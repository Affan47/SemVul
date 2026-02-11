getJavaFieldInt(JNIEnv *env, jobject obj, const char *name)
{
    jclass clazz = (*env)->GetObjectClass(env, obj);
    jfieldID fieldId =  (*env)->GetFieldID(env, clazz, name, "I");
    if(!fieldId)
    {
        char strErr[255];
        sprintf(strErr, "Java Object Field is not found: int %s !!!", name);
        throwNewJavaSecurityException(env, strErr);
    }
    int val = (*env)->GetIntField(env, obj, fieldId);
    (*env)->DeleteLocalRef(env, clazz);
    return val;
}
