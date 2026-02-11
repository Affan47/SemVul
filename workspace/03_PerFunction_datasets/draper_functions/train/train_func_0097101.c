CommandDown(GRPENT *pGE, CONSCLIENT *pCLServing, CONSENT *pCEServing,
	    long tyme)
#else
CommandDown(pGE, pCLServing, pCEServing, tyme)
    GRPENT *pGE;
    CONSCLIENT *pCLServing;
    CONSENT *pCEServing;
    long tyme;
#endif
{
    CONSCLIENT *pCL;

    if (!pCLServing->fwr) {
	FileWrite(pCLServing->fd, FLAGFALSE, "attach to down line]\r\n",
		  -1);
	return;
    }
    if (!pCEServing->fup) {
	FileWrite(pCLServing->fd, FLAGFALSE, "ok]\r\n", -1);
	return;
    }

    ConsDown(pCEServing, FLAGFALSE, FLAGFALSE);
    FileWrite(pCLServing->fd, FLAGFALSE, "line down]\r\n", -1);


    for (pCL = pCEServing->pCLon; (CONSCLIENT *)0 != pCL;
	 pCL = pCL->pCLnext) {
	if (pCL == pCLServing)
	    continue;
	if (pCL->fcon) {
	    FilePrint(pCL->fd, FLAGFALSE, "[line down by %s]\r\n",
		      pCLServing->acid->string);
	}
    }
}
