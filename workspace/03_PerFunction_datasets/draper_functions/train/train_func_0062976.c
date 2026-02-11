Itcl_EnsembleInit(interp)
    Tcl_Interp *interp;
{
    if (Tcl_GetObjType(itclEnsInvocType.name) == NULL) {
        Tcl_RegisterObjType(&itclEnsInvocType);
    }

    Tcl_CreateObjCommand(interp, "::itcl::ensemble",
        Itcl_EnsembleCmd, (ClientData)NULL, (Tcl_CmdDeleteProc*)NULL);

    return TCL_OK;
}
