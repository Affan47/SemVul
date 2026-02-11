Itcl_BiIsaCmd(clientData, interp, objc, objv)
    ClientData clientData;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
{
    ItclClass *contextClass, *cdefn;
    ItclObject *contextObj;
    char *token;


    if (Itcl_GetContext(interp, &contextClass, &contextObj) != TCL_OK) {
        return TCL_ERROR;
    }

    if (!contextObj) {
        Tcl_AppendResult(interp,
            "improper usage: should be \"object isa className\"",
            (char*)NULL);
        return TCL_ERROR;
    }
    if (objc != 2) {
        token = Tcl_GetStringFromObj(objv[0], (int*)NULL);
        Tcl_AppendResult(interp,
            "wrong # args: should be \"object ", token, " className\"",
            (char*)NULL);
        return TCL_ERROR;
    }


    token = Tcl_GetStringFromObj(objv[1], (int*)NULL);
    cdefn = Itcl_FindClass(interp, token,  1);
    if (cdefn == NULL) {
        return TCL_ERROR;
    }

    if (Itcl_ObjectIsa(contextObj, cdefn)) {
        Tcl_SetIntObj(Tcl_GetObjResult(interp), 1);
    } else {
        Tcl_SetIntObj(Tcl_GetObjResult(interp), 0);
    }
    return TCL_OK;
}
