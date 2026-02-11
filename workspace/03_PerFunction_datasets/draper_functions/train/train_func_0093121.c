htmlByteOffsetCmd(clientData, interp, objc, objv)
    ClientData clientData;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
{
    int iCharOffset;
    int iRet;
    char *zArg;

    if (objc != 3) {
        Tcl_WrongNumArgs(interp, 1, objv, "STRING CHAR-OFFSET");
        return TCL_ERROR;
    }

    if (Tcl_GetIntFromObj(interp, objv[2], &iCharOffset)) return TCL_ERROR;
    zArg = Tcl_GetString(objv[1]);

    iRet = (Tcl_UtfAtIndex(zArg, iCharOffset) - zArg);
    Tcl_SetObjResult(interp, Tcl_NewIntObj(iRet));
    return TCL_OK;
}
