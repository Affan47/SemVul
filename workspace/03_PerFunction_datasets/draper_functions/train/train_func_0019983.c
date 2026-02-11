PoolDescriptionCmd(ClientData arg, Tcl_Interp *interp, int argc,
        CONST char **argv)
{
    if (argc != 2) {
        Tcl_AppendResult(interp, "wrong # of args: should be \"",
             (char*)argv[0], " poolname\"", NULL);
        return TCL_ERROR;
    }
    Tcl_SetResult(interp, Ns_DbPoolDescription((char*)argv[1]),TCL_STATIC);
    return TCL_OK;
}
