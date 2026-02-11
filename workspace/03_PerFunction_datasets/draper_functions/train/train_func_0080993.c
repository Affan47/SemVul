dns_util_spawn(char *cmd, char **argv, int stdout)
{
    int status;
    pid_t pchild, pgchild, rpid;

    if ((pchild = fork()) < 0) {
        plog_error(LOG_ERR, MODULE, "fork() failed");
        return -1;
    }

    if (pchild == 0) {


        if (stdout > 0 && dup2(stdout, 1) < 0)
            exit(EXIT_FAILURE);
        if ((pgchild = fork()) < 0)
            exit(EXIT_FAILURE);

        if (pgchild == 0) {
            if (execvp(cmd, argv) < 0) {
                plog_error(LOG_ERR, MODULE, "execvp() faild: %s", cmd);
                exit(EXIT_FAILURE);
            }
        }

        exit(EXIT_SUCCESS);
    } else {

        if ((rpid = waitpid(pchild, &status, 0)) < 0) {
            plog_error(LOG_ERR, MODULE, "%s: waitpid() faild");
            return -1;
        } else if (rpid == pchild) {
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                plog(LOG_ERR, "%s: exec() faild: %s", MODULE, cmd);
                return -1;
            }
        }
    }

    return 0;
}
