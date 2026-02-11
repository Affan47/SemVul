lms_finish_slave(struct pinfo *pinfo, int (*finish)(const struct fds *fds))
{
    int r;

    if (pinfo->child <= 0)
        return 0;

    r = finish(&pinfo->master);
    if (r == 0)
        r = _waitpid(pinfo->child);
    else {
        r = kill(pinfo->child, SIGKILL);
        if (r < 0)
            perror("kill");
        else
            r =_waitpid(pinfo->child);
    }
    pinfo->child = 0;

    return r;
}
