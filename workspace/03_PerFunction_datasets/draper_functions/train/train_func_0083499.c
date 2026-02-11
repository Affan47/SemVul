restart_box(char **argv)
{
    int rc;

    if (!(rc = fork())) {


        gwthread_sleep(1.0);
        if (execvp(argv[0],argv) == -1)
            error(errno, "Unable to start new process.");
    } else if (rc == -1)
        error(errno, "Could not restart, exiting...");

    return rc == -1 ? -1 : 0;
}
