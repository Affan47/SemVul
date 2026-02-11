NsTclKillObjCmd(ClientData arg, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
{
    int pid, signal;

    if ((objc != 3) && (objc != 4)) {
      badargs:
        Tcl_WrongNumArgs(interp, 1, objv, "?-nocomplain? pid signal");
        return TCL_ERROR;
    }
    if (objc == 3) {
        if (Tcl_GetIntFromObj(interp, objv[1], &pid) != TCL_OK) {
            return TCL_ERROR;
        }
        if (Tcl_GetIntFromObj(interp, objv[2], &signal) != TCL_OK) {
            return TCL_ERROR;
        }
        if (kill(pid, signal) != 0) {
            Tcl_AppendStringsToObj(Tcl_GetObjResult(interp), "kill (\"",
                Tcl_GetString(objv[1]), ",",
                Tcl_GetString(objv[2]),
			    "\") failed:  ", Tcl_PosixError(interp), NULL);
            return TCL_ERROR;
        }
    } else {
        if (strcmp(Tcl_GetString(objv[1]), "-nocomplain") != 0) {
            goto badargs;
        }
        if (Tcl_GetIntFromObj(interp, objv[2], &pid) != TCL_OK) {
            return TCL_ERROR;
        }
        if (Tcl_GetIntFromObj(interp, objv[3], &signal) != TCL_OK) {
            return TCL_ERROR;
        }
        kill(pid, signal);
    }
    return TCL_OK;
}
