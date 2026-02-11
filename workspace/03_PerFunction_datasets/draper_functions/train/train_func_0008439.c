SendAllClientsMsg(GRPENT *pGE, char *message)
#else
SendAllClientsMsg(pGE, message)
    GRPENT *pGE;
    char *message;
#endif
{
    CONSCLIENT *pCL;

    if ((GRPENT *)0 == pGE) {
	return;
    }

    for (pCL = pGE->pCLall; (CONSCLIENT *)0 != pCL; pCL = pCL->pCLscan) {
	if (pCL->fcon) {
	    FileWrite(pCL->fd, FLAGFALSE, message, -1);
	}
    }
}
