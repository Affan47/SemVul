get_wirecolor(int id, int type, Nv_data * data, Tcl_Interp * interp)
{
    int colr;
    char *col;
    char err[255];

    if (type != SURF) {
	Tcl_SetResult(interp,
		      "Error: map object must be a surface in order to use get_wirecolor",
		      TCL_VOLATILE);
	return (TCL_ERROR);
    }

    if (GS_get_wire_color(id, &colr) == -1) {
	sprintf(err, "Error: id (%d) in get_wirecolor is invalid", id);
	Tcl_SetResult(interp, err, TCL_VOLATILE);
	return (TCL_ERROR);
    }

    if (colr == WC_COLOR_ATT) {
	Tcl_SetResult(interp, "UseMap", TCL_VOLATILE);
    }
    else {
	col = int_to_tcl_color(colr);
	Tcl_SetResult(interp, col, TCL_VOLATILE);
    }

    return (TCL_OK);
}
