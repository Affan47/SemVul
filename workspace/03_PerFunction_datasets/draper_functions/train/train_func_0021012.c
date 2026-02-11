FindPidTable(pid_t pid)
{
    pr_PidRecord *pRec;
    int keyHash = (int) (pid & PID_HASH_MASK);

    pRec =  pr_wp.pidTable[keyHash];
    while (pRec) {
	if (pRec->pid == pid) {
	    break;
	}
	pRec = pRec->next;
    }
    return pRec;
}
