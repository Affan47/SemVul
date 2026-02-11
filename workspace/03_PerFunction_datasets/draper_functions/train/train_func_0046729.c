initializeEncoding(JNIEnv *env)
{
    jstring propname = 0;
    jstring enc = 0;

    if ((*env)->EnsureLocalCapacity(env, 3) < 0)
        return;

    propname = (*env)->NewStringUTF(env, "sun.jnu.encoding");
    if (propname) {
        jboolean exc;
        enc = JNU_CallStaticMethodByName
                       (env,
                        &exc,
                        "java/lang/System",
                        "getProperty",
                        "(Ljava/lang/String;)Ljava/lang/String;",
                        propname).l;
        if (!exc) {
            if (enc) {
                const char* encname = (*env)->GetStringUTFChars(env, enc, 0);
                if (encname) {


                    if ((strcmp(encname, "8859_1") == 0) ||
                        (strcmp(encname, "ISO8859-1") == 0) ||
                        (strcmp(encname, "ISO8859_1") == 0))
                        fastEncoding = FAST_8859_1;
                    else if (strcmp(encname, "ISO646-US") == 0)
                        fastEncoding = FAST_646_US;
                    else if (strcmp(encname, "Cp1252") == 0 ||


                             strcmp(encname, "utf-16le") == 0)
                        fastEncoding = FAST_CP1252;
                    else {
                        fastEncoding = NO_FAST_ENCODING;
                        jnuEncoding = (jstring)(*env)->NewGlobalRef(env, enc);
                    }
                    (*env)->ReleaseStringUTFChars(env, enc, encname);
                }
            }
        } else {
            (*env)->ExceptionClear(env);
        }
    } else {
        (*env)->ExceptionClear(env);
    }
    (*env)->DeleteLocalRef(env, propname);
    (*env)->DeleteLocalRef(env, enc);


    String_getBytes_ID = (*env)->GetMethodID(env, JNU_ClassString(env),
                                             "getBytes", "(Ljava/lang/String;)[B");
    String_init_ID = (*env)->GetMethodID(env, JNU_ClassString(env),
                                         "<init>", "([BLjava/lang/String;)V");
}
