source_run_script (char *command, char *mountpoint)
{
    pid_t pid, external_pid;


    external_pid = fork();
    switch (external_pid)
    {
        case 0:
            switch (pid = fork ())
            {
                case -1:
                    ERROR2 ("Unable to fork %s (%s)", command, strerror (errno));
                    break;
                case 0:
                    if (access(command, R_OK|X_OK) != 0) {
                        ERROR2 ("Unable to run command %s (%s)", command, strerror(errno));
                        exit(1);
                    }
                    DEBUG1 ("Starting command %s", command);
                    __setup_empty_script_environment();

                    execl(command, command, mountpoint, (char *)NULL);
                    exit(1);
                default:
                    break;
            }
            exit (0);
        case -1:
            ERROR1 ("Unable to fork %s", strerror (errno));
            break;
        default:
            waitpid (external_pid, NULL, 0);
            break;
    }
}
