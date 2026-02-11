NsTclNsvAppendObjCmd(ClientData arg, Tcl_Interp *interp, int objc, Tcl_Obj **objv)
{
    Array *arrayPtr;
    int i, new;
    Tcl_HashEntry *hPtr;

    if (objc < 4) {
    	Tcl_WrongNumArgs(interp, 1, objv, "array key string ?string ...?");
	return TCL_ERROR;
    }
    arrayPtr = LockArray(arg, interp, objv[1], 1);
    hPtr = Tcl_CreateHashEntry(&arrayPtr->vars, Tcl_GetString(objv[2]), &new);
    if (!new) {
	Tcl_SetResult(interp, Tcl_GetHashValue(hPtr), TCL_VOLATILE);
    }
    for (i = 3; i < objc; ++i) {
	Tcl_AppendResult(interp, Tcl_GetString(objv[i]), NULL);
    }
    UpdateVar(hPtr, Tcl_GetObjResult(interp));
    UnlockArray(arrayPtr);
    return TCL_OK;
}
