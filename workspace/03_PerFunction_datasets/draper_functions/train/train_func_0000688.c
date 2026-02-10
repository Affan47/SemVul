JVM_FindClassFromClassLoader(JNIEnv *env, const char *name,
                                    jboolean init, jobject loader,
                                    jboolean throw_error) {
    Class *class;

    TRACE("JVM_FindClassFromClassLoader(env=%p, name=%s, init=%d, loader=%p,"
          " throw_error=%d)", env, name, init, loader, throw_error);

    class = findClassFromClassLoader((char *)name, loader);

    if(class == NULL) {
        if(!throw_error) {
            Object *excep = exceptionOccurred();
            char *dot_name = slash2DotsDup((char*)name);

            clearException();
            signalChainedException(java_lang_ClassNotFoundException,
                                   dot_name, excep);
            sysFree(dot_name);
        }
    } else if(init)
        initClass(class);

    return class;
}
