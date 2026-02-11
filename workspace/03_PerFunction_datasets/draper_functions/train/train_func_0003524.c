daemon_init(struct daemon_info* di, const char* path, ...)
{
    int i;
    int numargs;
    va_list ap;

    di->di_stderr_fd[0] = -1;
    di->di_stderr_fd[1] = -1;
    di->di_stderr = NULL;
    di->di_pid = -1;
    di->di_path = strdup(path);

    va_start(ap, path);
    for (numargs = 0; va_arg(ap, char*) != NULL; ++numargs);
    va_end(ap);


    ++numargs;
    di->di_arguments = (char**)malloc(sizeof(char*) * numargs);
    if (di->di_arguments == NULL) {
        goto bail_out;
    }
    memset(di->di_arguments, 0, sizeof(char*) * numargs);
    di->di_numarguments = numargs;
    va_start(ap, path);
    for (i = 0; i < numargs; i++) {
        di->di_arguments[i] = va_arg(ap, char*);
        if (di->di_arguments[i] != NULL) {
            di->di_arguments[i] = strdup(di->di_arguments[i]);
            if (di->di_arguments[i] == NULL) {
                goto bail_out;
            }
        }
    }
    va_end(ap);

    return true;

bail_out:
    if (di->di_path != NULL) {
        free(di->di_path);
        di->di_path = NULL;
    }
    if (di->di_arguments != NULL) {
        for(i = 0; di->di_arguments[i] != NULL; i++) {
            free(di->di_arguments[i]);
        }
        free(di->di_arguments);
        di->di_arguments = NULL;
    }

    return false;
}
