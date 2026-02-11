Nget_val_at_xy_cmd(Nv_data * data, Tcl_Interp * interp,
		       int argc,
		       char **argv
    )
{
    float x, y;
    int id, att;
    char valstr[1024];
    double atof();

    if (argc != 5)
	return (TCL_ERROR);

    id = get_idnum(argv[1]);
    att = att_atoi(argv[2]);
    x = (float)atof(argv[3]);
    y = (float)atof(argv[4]);

    GS_get_val_at_xy(id, att, valstr, x, y);

    Tcl_SetResult(interp, valstr, TCL_VOLATILE);

    return (TCL_OK);

}
