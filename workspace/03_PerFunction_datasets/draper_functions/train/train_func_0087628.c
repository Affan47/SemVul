attachCurrentThread(void **penv, void *args, int is_daemon) {
    if(threadSelf() == NULL) {
        char *name = NULL;
        Object *group = NULL;

        if(args != NULL) {
            JavaVMAttachArgs *attach_args = (JavaVMAttachArgs*)args;

            if(!isSupportedJNIVersion(attach_args->version))
                return JNI_EVERSION;

            name = attach_args->name;
            group = attach_args->group;
        }

        if(attachJNIThread(name, is_daemon, group) == NULL)
            return JNI_ERR;

        if(!initJNILrefs())
            return JNI_ERR;
    }

    *penv = &jni_env;
    return JNI_OK;
}
