DbConfigPathCmd(ClientData arg, Tcl_Interp *interp, int argc, CONST char **argv)
{
    InterpData *idataPtr = arg;
    char *section;

    if (argc != 1) {
        Tcl_AppendResult(interp, "wrong # of args: should be \"", argv[0],
			 "\"", NULL);
        return TCL_ERROR;
    }
    section = Ns_ConfigGetPath(idataPtr->server, NULL, "db", NULL);
    Tcl_SetResult(interp, section, TCL_STATIC);
    return TCL_OK;
}
