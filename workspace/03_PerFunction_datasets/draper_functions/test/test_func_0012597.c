change_directory(wsh_command *cmd) {

    char *path = cmd->args2D[1];


    if (1 >= cmd->nargs) {
        path = getenv("HOME");
    }

    if (0 != chdir(path)) {
        perror("wsh");
        return APPLICATION_FAILURE;
    }

    return OK;

}
