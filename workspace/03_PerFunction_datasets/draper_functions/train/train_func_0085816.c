Itcl_StubExistsCmd(clientData, interp, objc, objv)
    ClientData clientData;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
{
    char *cmdName;
    Tcl_Command cmd;

    if (objc != 2) {
        Tcl_WrongNumArgs(interp, 1, objv, "name");
        return TCL_ERROR;
    }
    cmdName = Tcl_GetStringFromObj(objv[1], (int*)NULL);

    cmd = Tcl_FindCommand(interp, cmdName, (Tcl_Namespace*)NULL, 0);

    if (cmd != NULL && Itcl_IsStub(cmd)) {
        Tcl_SetIntObj(Tcl_GetObjResult(interp), 1);
    } else {
        Tcl_SetIntObj(Tcl_GetObjResult(interp), 0);
    }
    return TCL_OK;
}
