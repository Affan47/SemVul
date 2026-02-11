Exp_OpenObjCmd(
    ClientData clientData,
    Tcl_Interp *interp,
    int objc,
    Tcl_Obj *CONST objv[])
{
    ExpState *esPtr;
    char *chanName = 0;
    int newfd;
    int leaveopen = FALSE;
    Tcl_Channel channel;

    static char* options[] = {
	"-i",
	"-leaveopen",
	NULL
    };
    enum options {
	OPEN_ID,
	OPEN_LEAVEOPEN
    };
    int i;

    for (i=1; i<objc; i++) {
	char *name;
	int index;

	name = Tcl_GetString(objv[i]);
	if (name[0] != '-') {
	    break;
	}
	if (Tcl_GetIndexFromObj(interp, objv[i], options, "flag", 0,
			&index) != TCL_OK) {
	    goto usage;
	}
	switch ((enum options) index) {
	    case OPEN_ID:
		i++;
		if (i >= objc) goto usage;
		chanName = Tcl_GetString (objv[i]);
		break;
	    case OPEN_LEAVEOPEN:
		leaveopen = TRUE;
		break;
	}
    }

    if (!chanName) {
	esPtr = expStateCurrent(interp,1,0,0);
    } else {
	esPtr = expStateFromChannelName(interp,chanName,1,0,0,"exp_open");
    }
    if (!esPtr) return TCL_ERROR;


    if (-1 == (newfd = dup(esPtr->fdin))) {
	exp_error(interp,"dup: %s",Tcl_PosixError(interp));
	return TCL_ERROR;
    }

    if (!leaveopen) {

	if (esPtr->pid != EXP_NOPID) {
	    Tcl_Pid pid = (Tcl_Pid)(long)esPtr->pid;
	    Tcl_DetachPids(1,&pid);
	    esPtr->pid = EXP_NOPID;
	    esPtr->sys_waited = esPtr->user_waited = TRUE;
	}
	exp_close(interp,esPtr);
    }


    channel = Tcl_MakeFileChannel((ClientData)(long)newfd,TCL_READABLE|TCL_WRITABLE);
    Tcl_RegisterChannel(interp, channel);
    Tcl_AppendResult(interp, Tcl_GetChannelName(channel), (char *) NULL);
    return TCL_OK;

    usage:
    exp_error(interp,"usage: -i spawn_id");
    return TCL_ERROR;
}
