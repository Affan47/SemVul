Itcl_FindClass(interp, path, autoload)
    Tcl_Interp* interp;
    CONST char* path;
    int autoload;
{
    Tcl_Namespace* classNs;


    classNs = Itcl_FindClassNamespace(interp, path);

    if (classNs && Itcl_IsClassNamespace(classNs)) {
        return (ItclClass*)classNs->clientData;
    }


    if (autoload) {
        if (Tcl_VarEval(interp, "::auto_load ", path, (char*)NULL) != TCL_OK) {
            char msg[256];
            sprintf(msg, "\n    (while attempting to autoload class \"%.200s\")", path);
            Tcl_AddErrorInfo(interp, msg);
            return NULL;
        }
        Tcl_ResetResult(interp);

        classNs = Itcl_FindClassNamespace(interp, path);
        if (classNs && Itcl_IsClassNamespace(classNs)) {
            return (ItclClass*)classNs->clientData;
        }
    }

    Tcl_AppendResult(interp, "class \"", path, "\" not found in context \"",
        Tcl_GetCurrentNamespace(interp)->fullName, "\"",
        (char*)NULL);

    return NULL;
}
