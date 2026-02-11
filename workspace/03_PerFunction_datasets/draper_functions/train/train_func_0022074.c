EvalThread(void *arg)
{
    Tcl_Interp *interp;
    Tcl_DString ds;
    Tcl_DString unameDS;
    char buf[64], *res;
    int n, len, ncmd, stop;
    Sess *sessPtr = arg;
    char *server = sessPtr->modPtr->server;


    interp = NULL;
    Tcl_DStringInit(&ds);
    Tcl_DStringInit(&unameDS);
    sprintf(buf, "-nscp:%d-", sessPtr->id);
    Ns_ThreadSetName(buf);
    Ns_Log(Notice, "nscp: %s connected", ns_inet_ntoa(sessPtr->sa.sin_addr));
    if (!Login(sessPtr, &unameDS)) {
	goto done;
    }

    sessPtr->user = Tcl_DStringValue(&unameDS);


    interp = Ns_TclAllocateInterp(server);


    stop = 0;
    Tcl_CreateCommand(interp, "exit", ExitCmd, (ClientData) &stop, NULL);

    ncmd = 0;
    while (!stop) {
	Tcl_DStringTrunc(&ds, 0);
	++ncmd;
retry:
	sprintf(buf, "%s:nscp %d> ", server, ncmd);
	while (1) {
	    if (!GetLine(sessPtr->sock, buf, &ds, 1)) {
		goto done;
	    }
	    if (Tcl_CommandComplete(ds.string)) {
		break;
	    }
	    sprintf(buf, "%s:nscp %d>>> ", server, ncmd);
	}
	while (ds.length > 0 && ds.string[ds.length-1] == '\n') {
	    Tcl_DStringTrunc(&ds, ds.length-1);
	}
	if (STREQ(ds.string, "")) {
	    goto retry;
	}

        if (sessPtr->modPtr->commandLogging) {
            Ns_Log(Notice, "nscp: %s %d: %s", sessPtr->user, ncmd, ds.string);
        }

	if (Tcl_RecordAndEval(interp, ds.string, 0) != TCL_OK) {
	    Ns_TclLogError(interp);
	}
	Tcl_AppendResult(interp, "\r\n", NULL);
        res = Tcl_GetStringResult(interp);
	len = strlen(res);
	while (len > 0) {
	    if ((n = send(sessPtr->sock, res, len, 0)) <= 0) goto done;
	    len -= n;
	    res += n;
	}

        if (sessPtr->modPtr->commandLogging) {
            Ns_Log(Notice, "nscp: %s %d: done", sessPtr->user, ncmd);
        }
    }
done:
    Tcl_DStringFree(&ds);
    Tcl_DStringFree(&unameDS);
    if (interp != NULL) {
    	Ns_TclDeAllocateInterp(interp);
    }
    Ns_Log(Notice, "nscp: %s disconnected", ns_inet_ntoa(sessPtr->sa.sin_addr));
    ns_sockclose(sessPtr->sock);
    ns_free(sessPtr);
}
