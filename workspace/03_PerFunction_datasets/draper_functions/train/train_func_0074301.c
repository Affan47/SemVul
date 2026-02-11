av_start_prog(struct proginfo *pi)
{
    char *cmdline = get_cmdline(pi->prog);
    av_log(AVLOG_DEBUG, "Starting program %s", cmdline);
    av_free(cmdline);

    pi->pid = fork();

    if(pi->pid == -1) {
        av_log(AVLOG_ERROR, "Fork failed: %s", strerror(errno));
        return -EIO;
    }
    if(pi->pid == 0) {
        if(pi->wd != NULL)
            chdir(pi->wd);

        setsid();

        if(pi->ifd != -1) dup2(pi->ifd, 0);
        if(pi->ofd != -1) dup2(pi->ofd, 1);
        if(pi->efd != -1) dup2(pi->efd, 2);

        execvp(pi->prog[0], (char **) pi->prog);
        av_log(AVLOG_ERROR, "Failed to exec %s", pi->prog[0]);
        _exit(1);
    }

    return 0;
}
