dotread(ClientData clientData, Tcl_Interp * interp,
#ifndef TCLOBJ
		   int argc, char *argv[]
#else
		   int argc, Tcl_Obj * CONST objv[]
#endif
    )
{
    Agraph_t *g;
    Tcl_Channel channel;
    int mode;
    ictx_t *ictx = (ictx_t *)clientData;

    ictx->myioDisc.afread = myiodisc_afread;

    if (argc < 2) {
	Tcl_AppendResult(interp, "Wrong # args: should be \"", argv[0], " fileHandle\"", NULL);
	return TCL_ERROR;
    }
    channel = Tcl_GetChannel(interp, argv[1], &mode);
    if (channel == NULL || !(mode & TCL_READABLE)) {
	Tcl_AppendResult(interp, "\nChannel \"", argv[1], "\"", "is unreadable.", NULL);
	return TCL_ERROR;
    }


    g = agread ((FILE*)channel, (Agdisc_t *)clientData);
    if (!g) {
	Tcl_AppendResult(interp, "\nFailure to read graph \"", argv[1], "\"", NULL);
	if (agerrors()) {
	    Tcl_AppendResult(interp, " because of syntax errors.", NULL);
	}
	return TCL_ERROR;
    }
    if (agerrors()) {
	Tcl_AppendResult(interp, "\nSyntax errors in file \"", argv[1], " \"", NULL);
	return TCL_ERROR;
    }
    Tcl_AppendResult(interp, obj2cmd(g), NULL);
    return TCL_OK;
}
