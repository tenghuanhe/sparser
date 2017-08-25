#include "SparserSpark.h"
#include <jni.h>
#include <stdlib.h>
#include <iostream>
// #include "common.h"
// #include "rapidjson/document.h"
// #include "rapidjson/error/en.h"
// #include "rapidjson/stringbuffer.h"
// #include "rapidjson/writer.h"
// #include "sparser.h"

/*
using namespace rapidjson;

// Performs a parse of the query using RapidJSON. Returns true if all the
// predicates match.
bool rapidjson_parse(const char *line) {
    Document d;
    d.Parse(line);
    if (d.HasParseError()) {
        fprintf(stderr, "\nError(offset %u): %s\n",
                (unsigned)d.GetErrorOffset(),
                GetParseError_En(d.GetParseError()));
        fprintf(stderr, "Error line: %s", line);
        return false;
    }

    Value::ConstMemberIterator itr = d.FindMember("text");
    if (itr == d.MemberEnd()) {
        // The field wasn't found.
        return false;
    }
    if (strstr(itr->value.GetString(), "Putin") == NULL) {
        return false;
    }

    if (strstr(itr->value.GetString(), "Russia") == NULL) {
        return false;
    }

    return true;
}
*/

JNIEXPORT void JNICALL Java_SparserSpark_parse(JNIEnv *env, jobject obj,
                                               jstring str_java,
                                               jlong buffer_addr_java,
                                               jlong capacity) {
    // Step 1: Convert the Java String (jstring) into C string (char*)
    char *str_c = (char *)env->GetStringUTFChars(str_java, NULL);
    if (NULL == str_c) return;
    printf("In C, the string is: %s\n", str_c);
    env->ReleaseStringUTFChars(str_java, str_c);  // release resources

    // Step 2: We pass the raw address as a Java long (jlong); just cast to int
    // *
    int *buf = (int *)buffer_addr_java;
    for (long i = 0; i < capacity / sizeof(int); ++i) {
        int *curr_row = buf + i;
        *curr_row = rand() % 10;
    }
    printf("In C, the address is %p\n", buf);
}
