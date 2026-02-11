Java_java_io_UnixFileSystem_createFileExclusively(JNIEnv *env, jclass cls,
                                                  jstring pathname)
{
    jboolean rv = JNI_FALSE;

    WITH_PLATFORM_STRING(env, pathname, path) {
        int fd;
        if (!strcmp (path, "/")) {
            fd = JVM_EEXIST;
        } else {
            fd = JVM_Open(path, JVM_O_RDWR | JVM_O_CREAT | JVM_O_EXCL, 0666);
        }
        if (fd < 0) {
            if (fd != JVM_EEXIST) {
                JNU_ThrowIOExceptionWithLastError(env, path);
            }
        } else {
            JVM_Close(fd);
            rv = JNI_TRUE;
        }
    } END_PLATFORM_STRING(env, path);
    return rv;
}
