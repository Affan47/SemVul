Nchange_twist_cmd(Nv_data * data, Tcl_Interp * interp,
		      int argc,
		      char **argv
    )
{
    int twist;

    if (argc != 2)
	return (TCL_ERROR);
    twist = atoi(argv[1]);

    twist = (int)(10 * twist);
    GS_set_twist(twist);
    Nquick_draw_cmd(data, interp);

    return 0;
}
