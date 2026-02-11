getJavaMethodId(JNIEnv *env, jclass clazz, const char *name, const char *sig)
{
    jmethodID methodId = (*env)->GetMethodID(env, clazz,name,sig);
    if(!methodId)
    {
        char strErr[255];
        sprintf(strErr, "Java Method is not found: %s !!!", name);
        throwNewJavaSecurityException(env, strErr);
        return NULL;
    }

    return methodId;

}
