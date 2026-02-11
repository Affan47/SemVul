Itcl_ClassConstructorCmd(clientData, interp, objc, objv)
    ClientData clientData;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
{
    ItclObjectInfo *info = (ItclObjectInfo*)clientData;
    ItclClass *cdefnPtr = (ItclClass*)Itcl_PeekStack(&info->cdefnStack);

    char *name, *arglist, *body;

    if (objc < 3 || objc > 4) {
        Tcl_WrongNumArgs(interp, 1, objv, "args ?init? body");
        return TCL_ERROR;
    }

    name = Tcl_GetStringFromObj(objv[0], (int*)NULL);
    if (Tcl_FindHashEntry(&cdefnPtr->functions, name)) {
        Tcl_AppendResult(interp,
            "\"", name, "\" already defined in class \"",
            cdefnPtr->fullname, "\"",
            (char*)NULL);
        return TCL_ERROR;
    }


    arglist = Tcl_GetString(objv[1]);
    if (objc == 3) {
        body = Tcl_GetString(objv[2]);
    } else {
        cdefnPtr->initCode = Tcl_DuplicateObj(objv[2]);
        Tcl_IncrRefCount(cdefnPtr->initCode);
        body = Tcl_GetString(objv[3]);
    }

    if (Itcl_CreateMethod(interp, cdefnPtr, name, arglist, body) != TCL_OK) {
        return TCL_ERROR;
    }
    return TCL_OK;
}
