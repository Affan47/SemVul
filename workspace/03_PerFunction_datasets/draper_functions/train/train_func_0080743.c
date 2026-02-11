Itk_ArchOptUsualCmd(clientData, interp, objc, objv)
    ClientData clientData;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
{
    ArchMergeInfo *mergeInfo = (ArchMergeInfo*)clientData;

    CONST char *tag;
    Tcl_HashEntry *entry;
    Tcl_Obj *codePtr;

    if (objc > 2) {
        Tcl_WrongNumArgs(interp, 1, objv, "?tag?");
        return TCL_ERROR;
    }


    if (!mergeInfo->archInfo || !mergeInfo->optionTable) {
        char *token = Tcl_GetStringFromObj(objv[0], (int*)NULL);
        Tcl_AppendStringsToObj(Tcl_GetObjResult(interp),
            "improper usage: \"", token,
            "\" should only be accessed via itk_component",
            (char*)NULL);
        return TCL_ERROR;
    }


    if (objc == 2) {
        tag = Tcl_GetStringFromObj(objv[1], (int*)NULL);
    } else {
        tag = Tk_Class(mergeInfo->archComp->tkwin);
    }


    entry = Tcl_FindHashEntry(&mergeInfo->usualCode, tag);
    if (entry) {
        codePtr = (Tcl_Obj*)Tcl_GetHashValue(entry);
        return Tcl_EvalObj(interp, codePtr);
    }

    Tcl_AppendStringsToObj(Tcl_GetObjResult(interp),
        "can't find usual code for tag \"", tag, "\"",
        (char*)NULL);
    return TCL_ERROR;
}
