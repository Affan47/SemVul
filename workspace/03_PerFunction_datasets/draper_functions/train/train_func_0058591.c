BadArgs(Tcl_Interp *interp, char **argv, char *args)
{
    Tcl_AppendResult(interp, "wrong # args: should be \"",
        argv[0], " ", argv[1], NULL);
    if (args != NULL) {
        Tcl_AppendResult(interp, " ", args, NULL);
    }
    Tcl_AppendResult(interp, "\"", NULL);

    return TCL_ERROR;
}
