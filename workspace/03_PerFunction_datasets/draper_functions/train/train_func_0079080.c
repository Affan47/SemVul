JNU_ThrowByNameWithLastError(JNIEnv *env, const char *name,
                             const char *defaultDetail)
{
    char buf[256];
    int n = JVM_GetLastErrorString(buf, sizeof(buf));

    if (n > 0) {
        jstring s = JNU_NewStringPlatform(env, buf);
        if (s != NULL) {
            jobject x = JNU_NewObjectByName(env, name,
                                            "(Ljava/lang/String;)V", s);
            if (x != NULL) {
                (*env)->Throw(env, x);
            }
        }
    }
    if (!(*env)->ExceptionOccurred(env)) {
        JNU_ThrowByName(env, name, defaultDetail);
    }
}
