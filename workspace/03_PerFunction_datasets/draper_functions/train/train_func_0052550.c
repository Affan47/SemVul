makeChannel(MprCmd *cmd, int index)
{
    MprCmdFile      *file;
    int             fds[2];

    file = &cmd->files[index];

    if (pipe(fds) < 0) {
        mprError("Can't create stdio pipes. Err %d", mprGetOsError());
        return MPR_ERR_CANT_CREATE;
    }
    if (index == MPR_CMD_STDIN) {
        file->clientFd = fds[0];
        file->fd = fds[1];
    } else {
        file->clientFd = fds[1];
        file->fd = fds[0];
    }
    fcntl(file->fd, F_SETFL, fcntl(file->fd, F_GETFL) | O_NONBLOCK);
    mprLog(7, "makeCmdIO: pipe handles[%d] read %d, write %d", index, fds[0], fds[1]);
    return 0;
}
