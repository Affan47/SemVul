Itcl_GetEnsembleUsage(interp, ensName, objPtr)
    Tcl_Interp *interp;
    CONST char *ensName;
    Tcl_Obj *objPtr;
{
    CONST char **nameArgv = NULL;
    int nameArgc;
    Ensemble *ensData;
    Itcl_InterpState state;


    state = Itcl_SaveInterpState(interp, TCL_OK);

    if (Tcl_SplitList(interp, ensName, &nameArgc,
	    &nameArgv) != TCL_OK) {
        goto ensUsageFail;
    }
    if (FindEnsemble(interp, nameArgv, nameArgc, &ensData) != TCL_OK) {
        goto ensUsageFail;
    }
    if (ensData == NULL) {
        goto ensUsageFail;
    }


    GetEnsembleUsage(ensData, objPtr);

    Itcl_DiscardInterpState(state);
    return 1;

ensUsageFail:
    Itcl_RestoreInterpState(interp, state);
    return 0;
}
