isExecutable(const char* filename) {
    struct stat buf;
    if (!filename || stat(filename, &buf))
        return false;

    return buf.st_mode & S_IXUSR ||
           buf.st_mode & S_IXGRP ||
           buf.st_mode & S_IXOTH;
}
