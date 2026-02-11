NsTclNsvExistsObjCmd(ClientData arg, Tcl_Interp *interp, int objc, Tcl_Obj **objv)
{
    Array *arrayPtr;
    int exists;

    if (objc != 3) {
    	Tcl_WrongNumArgs(interp, 1, objv, "array key");
	return TCL_ERROR;
    }
    exists = 0;
    arrayPtr = LockArray(arg, NULL, objv[1], 0);
    if (arrayPtr != NULL) {
    	if (Tcl_FindHashEntry(&arrayPtr->vars, Tcl_GetString(objv[2])) != NULL) {
	    exists = 1;
	}
    	UnlockArray(arrayPtr);
    }
    Tcl_SetBooleanObj(Tcl_GetObjResult(interp), exists);
    return TCL_OK;
}
