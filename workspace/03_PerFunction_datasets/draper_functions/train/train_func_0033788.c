SignalKids(int arg)
#else
SignalKids(arg)
    int arg;
#endif
{
    GRPENT *pGE;

    for (pGE = pGroups; pGE != (GRPENT *)0; pGE = pGE->pGEnext) {
	if (0 == pGE->imembers || -1 == pGE->pid)
	    continue;
	CONDDEBUG((1, "SignalKids(): sending pid %lu signal %d",
		   (unsigned long)pGE->pid, arg));
	if (-1 == kill(pGE->pid, arg)) {
	    Error("SignalKids(): kill(%lu): %s", (unsigned long)pGE->pid,
		  strerror(errno));
	}
    }
}
