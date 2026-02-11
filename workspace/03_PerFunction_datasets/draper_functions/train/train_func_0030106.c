Ndelete_key_cmd(Nv_data * data,
		    Tcl_Interp * interp,
		    int argc,
		    char **argv
    )
{

    double pos, precis;
    int justone;
    int num_deleted;
    char tmp[10];

    if (argc != 4) {
	Tcl_SetResult(interp, "Error: should be Ndelete_key pos precis justone", TCL_VOLATILE);
	return (TCL_ERROR);
    }

    if (Tcl_GetDouble(interp, argv[1], &pos) != TCL_OK)
	return TCL_ERROR;
    if (Tcl_GetDouble(interp, argv[2], &precis) != TCL_OK)
	return TCL_ERROR;
    if (Tcl_GetBoolean(interp, argv[3], &justone) != TCL_OK)
	return TCL_ERROR;


    num_deleted = GK_delete_key((float)pos, (float)precis, justone);

    sprintf(tmp, "%d", num_deleted);
    Tcl_SetResult(interp, tmp, TCL_VOLATILE);
    return (TCL_OK);

}
