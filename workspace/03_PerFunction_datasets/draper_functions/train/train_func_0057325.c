PROCwatch(pid_t pid, int site)
{
    PROCESS     *pp;
    int         i;


    for (pp = PROCtable, i = PROCtablesize; --i >= 0; pp++)
	if (pp->State == PSfree)
	    break;
    if (i < 0) {

        PROCtable = xrealloc(PROCtable, (PROCtablesize + 20) * sizeof(PROCESS));
        for (pp = &PROCtable[PROCtablesize], i=20; --i >= 0; pp++)
          *pp = PROCnull;
	pp = &PROCtable[PROCtablesize];
	PROCtablesize += 20;
    }

    pp->State = PSrunning;
    pp->Pid = pid;
    pp->Started = Now.tv_sec;
    pp->Site = site;
    return pp - PROCtable;
}
