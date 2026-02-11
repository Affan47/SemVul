absolutePath(char *path)
{
    char    *str, cwd[MAXPATH], *result;
    int     len;

	if (path == NULL || *path == '\0') {
		return path;
	}


    str = mapDelim(strdup(path));
    if (*str == '/') {
        return str;
    }
#if _WIN32 || __CYGWIN__
    if (strlen(path) > 3 && isalpha((int) path[0]) && path[1] == ':' && path[2] == '/') {
        return str;
    }
#endif

    cwd[sizeof(cwd) - 1] = '\0';
    if (getcwd(cwd, sizeof(cwd) - 1) == 0) {
        fprintf(stderr, "Cant get working directory");
        exit(255);
    }
    len = (int) strlen(cwd);
    result = malloc(len + strlen(path) + 2);

    strcpy(result, cwd);
    result[len] = '/';
    strcpy(&result[len + 1], path);

    return result;
}
