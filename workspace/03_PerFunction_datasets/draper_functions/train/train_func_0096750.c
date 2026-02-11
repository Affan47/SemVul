setlgt_position(Nv_data * data, Tcl_Interp * interp,
			   int argc,
			   char **argv
    )
{
    int num, w;
    float x, y, z;
    double atof();

    if (argc != 6)
	return (TCL_ERROR);

    num = get_light_num(argv[0]);

    data->light[num].x = x = (float)atof(argv[2]);
    data->light[num].y = y = (float)atof(argv[3]);
    data->light[num].z = z = (float)atof(argv[4]);
    data->light[num].w = w = (float)atoi(argv[5]);
    GS_setlight_position(num, x, y, z, w);
    return (TCL_OK);
}
