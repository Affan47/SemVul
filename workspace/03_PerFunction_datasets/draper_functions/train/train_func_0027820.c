Exp_CloseObjCmd(
    ClientData clientData,
    Tcl_Interp *interp,
    int objc,
    Tcl_Obj *CONST objv[])
{
    int onexec_flag = FALSE;
    int close_onexec;
    int slave_flag = FALSE;
    ExpState *esPtr = 0;
    char *chanName = 0;
    int i;

    static char* options[] = {
	"-i",
	"-onexec",
	"-slave",
	NULL
    };
    enum options {
	CLOSE_ID,
	CLOSE_ONEXEC,
	CLOSE_SLAVE
    };

    for (i=1; i<objc; i++) {
	char *name;
	int index;

	name = Tcl_GetString(objv[i]);
	if (name[0] != '-') {
	    break;
	}
	if (Tcl_GetIndexFromObj(interp, objv[i], options, "flag", 0,
			&index) != TCL_OK) {
	    return TCL_ERROR;
	}
	switch ((enum options) index) {
	    case CLOSE_ID:
		i++;
		if (i == objc) {
		    exp_error(interp,"usage: -i spawn_id");
		    return(TCL_ERROR);
		}
		chanName = Tcl_GetString(objv[i]);
		break;
	    case CLOSE_ONEXEC:
		i++;
		if (i == objc) {
		    on_exec_usage:
		    exp_error(interp,"usage: -onexec 0|1");
		    return(TCL_ERROR);
		}
		onexec_flag = TRUE;
		if (TCL_OK != Tcl_GetBooleanFromObj (interp, objv[i], &close_onexec)) {
		    goto on_exec_usage;
		}
		break;
	    case CLOSE_SLAVE:
		slave_flag = TRUE;
		break;
	}
    }

    if (i < objc) {


        Tcl_CmdInfo* close_info;

	Tcl_ResetResult(interp);

	close_info = (Tcl_CmdInfo*) Tcl_GetAssocData (interp, EXP_CMDINFO_CLOSE, NULL);
	return(close_info->objProc(close_info->objClientData,interp,objc,objv));
    }

    if (chanName) {
	esPtr = expStateFromChannelName(interp,chanName,1,0,0,"close");
    } else {
	esPtr = expStateCurrent(interp,1,0,0);
    }
    if (!esPtr) return TCL_ERROR;

    if (slave_flag) {
	if (esPtr->fd_slave != EXP_NOFD) {
	    close(esPtr->fd_slave);
	    esPtr->fd_slave = EXP_NOFD;

	    exp_slave_control(esPtr->fdin,1);

	    return TCL_OK;
	} else {
	    exp_error(interp,"no such slave");
	    return TCL_ERROR;
	}
    }

    if (onexec_flag) {


	fcntl(esPtr->fdin,F_SETFD,close_onexec);
	return TCL_OK;
    }

    return(exp_close(interp,esPtr));
}
