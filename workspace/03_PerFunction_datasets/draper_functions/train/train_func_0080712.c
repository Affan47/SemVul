NsTclGuessTypeObjCmd(ClientData dummy, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
{
    char *type;

    if (objc != 2) {
        Tcl_WrongNumArgs(interp, 1, objv, "filename");
        return TCL_ERROR;
    }
    type = Ns_GetMimeType(Tcl_GetString(objv[1]));
    Tcl_SetResult(interp, type, TCL_VOLATILE);

    return TCL_OK;
}
