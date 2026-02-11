trim(char *path)
{
    int     len;

    while (1) {
        len = (int) strlen(path);
        if (path[len - 1] == '/') {
            path[len - 1] = '\0';
        } else {
            return path;
        }
    }
    return path;
}
