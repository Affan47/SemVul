statMode(const char *path, int *mode)
{
    if (stat64_ptr) {
        struct stat64 sb;
        if (((*stat64_ptr)(path, &sb)) == 0) {
            *mode = sb.st_mode;
            return JNI_TRUE;
        }
    } else {
        struct stat sb;
        if (stat(path, &sb) == 0) {
            *mode = sb.st_mode;
            return JNI_TRUE;
        }
    }
    return JNI_FALSE;
}
