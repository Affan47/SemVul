gClose(GProc *proc, GPipe *gp, int force)
{
    int ret;

    if (proc->pid <= 0) {
        debug("whoops, gClose while helper not running\n");
        return 0;
    }
    _gClosen(&proc->pipe);
    if (gp)
        gClosen(gp);
    if (force)
        terminateProcess(proc->pid, SIGTERM);
    ret = Wait4(&proc->pid);
    if (wcSig(ret) ? wcSig(ret) != SIGTERM :
                     (wcCode(ret) < EX_NORMAL || wcCode(ret) > EX_MAX))
        logError("Abnormal termination of %s, code %d, signal %d\n",
                 proc->pipe.who, wcCode(ret), wcSig(ret));
    debug("closed %s\n", proc->pipe.who);
    free(proc->pipe.who);
    proc->pipe.who = 0;
    return ret;
}
