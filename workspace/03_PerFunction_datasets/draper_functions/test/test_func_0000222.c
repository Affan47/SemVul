daemon_sigchld(struct daemon_info* di, unsigned int waitbeforerestart)
{
#ifndef WIN32
    int status;

    waitpid(di->di_pid, &status, 0);
    if (waitbeforerestart != 0) {
        (void)sleep(waitbeforerestart);
    }
#endif
    return daemon_start(di);
}
