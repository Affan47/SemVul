check_blank(Tcl_Interp * interp, int map_id)
{
    const char *val, **listArgv;
    int listArgc, rval, i;


    val = Tcl_GetVar(interp, "NVIZ_BLANK_MAPS", TCL_GLOBAL_ONLY);
    if (val == NULL)
	return 0;


    if (Tcl_SplitList(interp, val, &listArgc, &listArgv) != TCL_OK) {
	return 0;
    }

    rval = 0;
    for (i = 0; (i < listArgc) & (!rval); i++) {
	if (map_id == atoi(listArgv[i])) {
	    rval = 1;
	}
    }

    Tcl_Free((char *)listArgv);
    return rval;

}
