Ns_After(int delay, Ns_Callback *proc, void *arg, Ns_Callback *deleteProc)
{
    if (delay < 0) {
	return NS_ERROR;
    }
    return Ns_ScheduleProcEx((Ns_SchedProc *) proc, arg, NS_SCHED_ONCE,
    	    	    	     delay, (Ns_SchedProc *) deleteProc);
}
