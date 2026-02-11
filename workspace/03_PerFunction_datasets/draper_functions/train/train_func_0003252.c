mprReadCmd(MprCmd *cmd, int channel, char *buf, ssize bufsize)
{
#if BLD_WIN_LIKE
{
    int     rc, count;


    mprAssert(cmd->files[channel].handle);
    rc = PeekNamedPipe(cmd->files[channel].handle, NULL, 0, NULL, &count, NULL);
    if (rc > 0 && count > 0) {
        return read(cmd->files[channel].fd, buf, (uint) bufsize);
    }
    if (cmd->process == 0 || WaitForSingleObject(cmd->process, 0) == WAIT_OBJECT_0) {

        return 0;
    }

    SetLastError(WSAEWOULDBLOCK);
    return -1;
}
#else
    mprAssert(cmd->files[channel].fd >= 0);
    return read(cmd->files[channel].fd, buf, bufsize);
#endif
}
