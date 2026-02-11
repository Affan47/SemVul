attach(pid_t target)
{
    int status;


    if (ptrace(PTRACE_ATTACH, target, NULL, NULL) == -1L) {
        show_error("failed to attach to %d, %s\n", target, strerror(errno));
        return false;
    }


    if (waitpid(target, &status, 0) == -1 || !WIFSTOPPED(status)) {
        show_error("there was an error waiting for the target to stop.\n");
        show_info("%s\n", strerror(errno));
        return false;
    }


    memset(&peekbuf, 0x00, sizeof(peekbuf));


    return true;

}
