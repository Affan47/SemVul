CommandOpen(GRPENT *pGE, CONSCLIENT *pCLServing, CONSENT *pCEServing,
	    long tyme)
#else
CommandOpen(pGE, pCLServing, pCEServing, tyme)
    GRPENT *pGE;
    CONSCLIENT *pCLServing;
    CONSENT *pCEServing;
    long tyme;
#endif
{
    CONSCLIENT *pCL;

    if (!pCLServing->fwr) {
	FileWrite(pCLServing->fd, FLAGFALSE, "attach to reopen]\r\n", -1);
	return;
    }


    ConsInit(pCEServing);
    if (pCEServing->fup &&
	(pCEServing->initfile != (CONSFILE *)0 ||
	 pCEServing->ioState == INCONNECT)) {
	FileWrite(pCLServing->fd, FLAGFALSE, "connecting...", -1);
	pCLServing->fiwait = 1;
    } else if (pCEServing->fronly) {
	FilePrint(pCLServing->fd, FLAGFALSE, "%s -- read-only]\r\n",
		  pCEServing->fup ? "up" : "down");
    } else if ((CONSCLIENT *)0 == (pCL = pCEServing->pCLwr)) {
	pCEServing->pCLwr = pCLServing;
	pCLServing->fwr = 1;
	FilePrint(pCLServing->fd, FLAGFALSE, "%s -- attached]\r\n",
		  pCEServing->fup ? "up" : "down");
	TagLogfileAct(pCEServing, "%s attached", pCLServing->acid->string);
    } else if (pCL == pCLServing) {
	FilePrint(pCLServing->fd, FLAGFALSE, "%s]\r\n",
		  pCEServing->fup ? "up" : "down");
	TagLogfileAct(pCEServing, "%s attached", pCLServing->acid->string);
    } else {
	FilePrint(pCLServing->fd, FLAGFALSE, "%s, %s is attached]\r\n",
		  pCEServing->fup ? "up" : "down", pCL->acid->string);
    }
}
