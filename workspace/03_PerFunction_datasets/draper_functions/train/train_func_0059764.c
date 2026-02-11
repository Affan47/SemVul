Java_java_io_UnixFileSystem_getLastModifiedTime(JNIEnv *env, jobject this,
                                                jobject file)
{
    jlong rv = 0;

    WITH_FIELD_PLATFORM_STRING(env, file, ids.path, path) {
        if (stat64_ptr) {
            struct stat64 sb;
            if (((*stat64_ptr)(path, &sb)) == 0) {
                rv = 1000 * (jlong)sb.st_mtime;
            }
        } else {
            struct stat sb;
            if (stat(path, &sb) == 0) {
                rv = 1000 * (jlong)sb.st_mtime;
            }
        }
    } END_PLATFORM_STRING(env, path);
    return rv;
}
