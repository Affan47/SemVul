Nset_fov_cmd(Nv_data * data, Tcl_Interp * interp,
		 int argc,
		 char **argv
    )
{
    int fov;

    if (argc != 2)
	return (TCL_ERROR);
    fov = atoi(argv[1]);
    fov = (int)(fov * 10);
    GS_set_fov(fov);

    return (TCL_OK);
}
