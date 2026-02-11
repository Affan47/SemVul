Kill(Proc *procPtr, int sig)
{
    Ns_Log(Warning, "[%s]: process %d won't die - sending sig %d",
	procPtr->poolPtr->name, procPtr->pid, sig);
    if (kill(procPtr->pid, sig) != 0 && errno != ESRCH) {
	Ns_Fatal("kill(%d, %d) failed: %s", procPtr->pid, sig, strerror(errno));
    }
}
