NsTclReturnBadRequestObjCmd(ClientData arg, Tcl_Interp *interp, int objc,
			    Tcl_Obj *CONST objv[])
{
    Ns_Conn *conn;
    char    *reason;

    if (objc != 2 && objc != 3) {
        Tcl_WrongNumArgs(interp, 1, objv, "?connid? reason");
        return TCL_ERROR;
    }
    if (objc == 3 && !NsTclCheckConnId(interp, objv[1])) {
	return TCL_ERROR;
    }
    if (NsTclGetConn((NsInterp *) arg, &conn) != TCL_OK) {
	return TCL_ERROR;
    }
    reason = Tcl_GetString(objv[objc-1]);
    return Result(interp, Ns_ConnReturnBadRequest(conn, reason));
}
