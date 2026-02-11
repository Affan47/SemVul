Nget_zrange_cmd(Nv_data * data, Tcl_Interp * interp,
		    int argc,
		    char **argv
    )
{
    float min, max;
    char *list[3], cmin[32], cmax[32];

    min = max = 0.0;
    if (argc > 2) {
	if (!strcmp(argv[2], "doexag"))
	    GS_get_zrange_nz(&min, &max);
	else if (!strcmp(argv[2], "nz"))
	    GS_get_zrange_nz(&min, &max);
	else
	    return (TCL_ERROR);
    }
    else
	GS_get_zrange_nz(&min, &max);

    sprintf(cmin, "%f", min);
    sprintf(cmax, "%f", max);
    list[0] = cmin;
    list[1] = cmax;
    list[2] = NULL;


    Tcl_SetResult(interp, Tcl_Merge(2, list), TCL_DYNAMIC);
    return (TCL_OK);
}
