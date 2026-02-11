GraceClose(void)
{
    if (fd_pipe == -1) {
        error_function("No grace subprocess1");
        return (-1);
    }


    if (pid > 0) {

        if ((GraceCommand ("exit") == -1 || _GraceFlush() == -1) && pid > 0) {
            kill(pid, SIGTERM);
        }
    }

    GraceCleanup();

    return (0);
}
