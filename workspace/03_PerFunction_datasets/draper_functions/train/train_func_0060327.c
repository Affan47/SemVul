chdir(const char *dir)
{
        size_t len;
        char *ptr;

        if (strcmp(dir, ".") == 0)
                return 0;

        if (*dir != '/') {
                if (strcmp(dir, "..") == 0) {
                        ptr = strrchr(path, '/');
                        if (ptr != path)
                                *ptr = '\0';
                } else {
                        len = strlen(path);
                        ptr = (char *)(*(path + 1) != '\0' ? "/" : "");
                        snprintf(path + len, MAX_PATHLEN - len, "%s%s", ptr, dir);
                }
        } else
                snprintf(path, MAX_PATHLEN, "%s", dir);

        return 0;
}
