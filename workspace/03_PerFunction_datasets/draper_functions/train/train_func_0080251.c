GetObjCmd(Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[], int byaddr)
{
    Ns_DString  ds;
    char       *opt, *addr;
    int         all = 0;
    int         status;

    if (byaddr) {
        if (objc < 2 || objc > 3) {
            Tcl_WrongNumArgs(interp, 1, objv, "?-all? address");
            return TCL_ERROR;
        }
    } else {
        if (objc != 2) {
            Tcl_WrongNumArgs(interp, 1, objv, "address");
            return TCL_ERROR;
        }
    }
    opt = Tcl_GetString(objv[1]);
    if (objc >= 3 && STREQ(opt, "-all")) {
        all = 1;
        addr = Tcl_GetString(objv[2]);
    } else {
        addr = opt;
    }

    Ns_DStringInit(&ds);
    if (byaddr) {
        if (all) {
            status = Ns_GetAllAddrByHost(&ds, addr);
        } else {
            status = Ns_GetAddrByHost(&ds, addr);
        }
    } else {
        status = Ns_GetHostByAddr(&ds, addr);
    }
    if (status == NS_TRUE) {
    	Tcl_SetResult(interp, ds.string, TCL_VOLATILE);
    }
    Ns_DStringFree(&ds);
    if (status != NS_TRUE) {
        Tcl_AppendResult(interp, "could not lookup ", addr, NULL);
	return TCL_ERROR;
    }
    return TCL_OK;
}
