resetCmd(MprCmd *cmd)
{
    MprCmdFile      *files;
    int             i;

    mprAssert(cmd);
    files = cmd->files;
    for (i = 0; i < MPR_CMD_MAX_PIPE; i++) {
        if (cmd->handlers[i]) {
            mprRemoveWaitHandler(cmd->handlers[i]);
            cmd->handlers[i] = 0;
        }
        if (files[i].clientFd >= 0) {
            close(files[i].clientFd);
            files[i].clientFd = -1;
        }
        if (files[i].fd >= 0) {
            close(files[i].fd);
            files[i].fd = -1;
        }
    }
    cmd->eofCount = 0;
    cmd->complete = 0;
    cmd->status = -1;

    if (cmd->pid && !(cmd->flags & MPR_CMD_DETACH)) {
        mprStopCmd(cmd, -1);
        reapCmd(cmd, 0);
        cmd->pid = 0;
    }
}
