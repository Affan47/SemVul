cmdNext(clientData, interp, objc, objv)
ClientData clientData;
Tcl_Interp *interp;
     int objc;
     Tcl_Obj *CONST objv[];
{
	debug_new_action = TRUE;
	debug_cmd = *(enum debug_cmd *)clientData;

	last_action_cmd = debug_cmd;

    if (objc == 1) {
	step_count = 1;
    } else if (TCL_OK != Tcl_GetIntFromObj (interp, objv[1], &step_count)) {
	return TCL_ERROR;
    }

	last_step_count = step_count;
	return(TCL_RETURN);
}
