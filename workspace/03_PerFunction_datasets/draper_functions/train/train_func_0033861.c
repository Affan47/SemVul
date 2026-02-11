Java_org_mortbay_setuid_SetUID_getpwuid(JNIEnv * env, jclass j, jint uid)
{
    struct passwd* pw;
    pw=getpwuid((uid_t) uid);
    if (!pw)
    {
        char strErr[255];
        sprintf(strErr, "User with uid %d is not found!!!", uid);
        throwNewJavaSecurityException(env, strErr);
        return NULL;
    }


    jclass cls;
    cls = (*env)->FindClass(env,"org/mortbay/setuid/Passwd");
    if(!cls)
    {
        throwNewJavaSecurityException(env, "Class: org.mortbay.setuid.Passwd is not found!!!");
        return NULL;
    }


    jmethodID constructorMethod = getJavaMethodId(env, cls, "<init>", "()V");


    jobject retVal = (*env)->NewObject(env, cls,constructorMethod);
    if(!retVal)
    {
        throwNewJavaSecurityException(env, "Object Construction error of Class: org.mortbay.setuid.Passwd!!!");
        return NULL;
    }


    setJavaFieldString(env, retVal, "_pwName", pw->pw_name);

    setJavaFieldString(env, retVal, "_pwPasswd", pw->pw_passwd);

    setJavaFieldInt(env, retVal, "_pwUid", pw->pw_uid);

    setJavaFieldInt(env, retVal, "_pwGid", pw->pw_gid);

    setJavaFieldString(env, retVal, "_pwGecos", pw->pw_gecos);

    setJavaFieldString(env, retVal, "_pwDir", pw->pw_dir);

    setJavaFieldString(env, retVal, "_pwShell", pw->pw_shell);

    (*env)->DeleteLocalRef(env, cls);
    return retVal;
}
