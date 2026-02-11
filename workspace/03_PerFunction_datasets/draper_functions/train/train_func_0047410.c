ScriptAddString_Cmd(ClientData clientData,

			Tcl_Interp * interp,
			int argc,
			char **argv
    )
{
    if (argc != 2) {
	Tcl_SetResult(interp, "Usage: Nv_script_add_string string",
		      TCL_VOLATILE);
	return (TCL_ERROR);
    }

    if (Nv_script_file != NULL) {
	fprintf(Nv_script_file, "%s\n", argv[1]);
    }

    return (TCL_OK);
}
