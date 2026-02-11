Rivet_GetTclFile(char *filename, Tcl_Obj *outbuf, Tcl_Interp *interp)
{
    int result = 0;


    Tcl_Channel chan = Tcl_OpenFileChannel(interp, filename, "r", 0644);
    if (chan == (Tcl_Channel) NULL)
    {
        Tcl_ResetResult(interp);
        Tcl_AppendResult(interp, "couldn't read file \"", filename,
                         "\": ", Tcl_PosixError(interp), (char *) NULL);
        return TCL_ERROR;
    }
    result = Tcl_ReadChars(chan, outbuf, -1, 1);
    if (result < 0)
    {
        Tcl_Close(interp, chan);
        Tcl_AppendResult(interp, "couldn't read file \"", filename,
                         "\": ", Tcl_PosixError(interp), (char *) NULL);
        return TCL_ERROR;
    }

    if (Tcl_Close(interp, chan) != TCL_OK)
        return TCL_ERROR;

    return TCL_OK;
}
