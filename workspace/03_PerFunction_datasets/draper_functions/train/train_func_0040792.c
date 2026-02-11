addCmdHandlers(MprCmd *cmd)
{
    int     stdinFd, stdoutFd, stderrFd;

    stdinFd = cmd->files[MPR_CMD_STDIN].fd;
    stdoutFd = cmd->files[MPR_CMD_STDOUT].fd;
    stderrFd = cmd->files[MPR_CMD_STDERR].fd;

    if (stdinFd >= 0 && cmd->handlers[MPR_CMD_STDIN] == 0) {
        cmd->handlers[MPR_CMD_STDIN] = mprCreateWaitHandler(stdinFd, MPR_WRITABLE, cmd->dispatcher, stdinCallback, cmd, 0);
    }
    if (stdoutFd >= 0 && cmd->handlers[MPR_CMD_STDOUT] == 0) {
        cmd->handlers[MPR_CMD_STDOUT] = mprCreateWaitHandler(stdoutFd, MPR_READABLE, cmd->dispatcher, stdoutCallback, cmd,0);
    }
    if (stderrFd >= 0 && cmd->handlers[MPR_CMD_STDERR] == 0) {
        cmd->handlers[MPR_CMD_STDERR] = mprCreateWaitHandler(stderrFd, MPR_READABLE, cmd->dispatcher, stderrCallback, cmd,0);
    }
}
