CommandLogging(GRPENT *pGE, CONSCLIENT *pCLServing, CONSENT *pCEServing,
	       long tyme)
#else
CommandLogging(pGE, pCLServing, pCEServing, tyme)
    GRPENT *pGE;
    CONSCLIENT *pCLServing;
    CONSENT *pCEServing;
    long tyme;
#endif
{
    if (pCLServing->fwr) {
	pCEServing->nolog = !pCEServing->nolog;
	if (pCEServing->nolog) {
	    FileWrite(pCLServing->fd, FLAGFALSE, "logging off]\r\n", -1);
	    TagLogfile(pCEServing, "Console logging disabled by %s",
		       pCLServing->acid->string);
	} else {
	    FileWrite(pCLServing->fd, FLAGFALSE, "logging on]\r\n", -1);
	    TagLogfile(pCEServing, "Console logging restored by %s",
		       pCLServing->acid->string);
	}
    } else {
	FilePrint(pCLServing->fd, FLAGFALSE,
		  "attach to toggle logging]\r\n");
    }
}
