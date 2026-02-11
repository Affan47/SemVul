CloseScripting_Cmd(ClientData clientData,

		       Tcl_Interp * interp,
		       int argc,
		       char **argv
    )
{
    if (argc != 1) {
	Tcl_SetResult(interp, "Usage: Nv_close_scripting", TCL_VOLATILE);
	return (TCL_ERROR);
    }

    if (Nv_script_file != NULL) {
	fprintf(Nv_script_file, "puts \"script complete\"\n");
	fclose(Nv_script_file);
    }

    return (TCL_OK);
}
