Npick_vect_cmd(data, interp, argc, argv)
     Nv_data *data;
     Tcl_Interp *interp;
     int argc;
     char **argv;
{
    float x, y, z, maxdist;
    int sx, sy, id;
    char *name;

    int *found_cats = NULL;
    int i, n_cats;
    char buf[2000];

    if (argc != 5)
	return (TCL_ERROR);

    sx = atoi(argv[1]);
    sy = atoi(argv[2]);
    name = argv[3];
    maxdist = atof(argv[4]);

#ifdef DEBUG_MSG
    fprintf(stderr, "x= %d  :  y= %d\n", sx, sy);
#endif

    if (!GS_get_selected_point_on_surface(sx, sy, &id, &x, &y, &z)) {
	sprintf(buf, "%s", "");
	Tcl_AppendElement(interp, buf);
	return (TCL_OK);
    }

    n_cats = query_vect_cats(name, x, y, maxdist, &found_cats);

    for (i = 0; i < n_cats; i++) {
	sprintf(buf, "%d", found_cats[i]);
	Tcl_AppendElement(interp, buf);
    }

    if (found_cats)
	free(found_cats);
    return (TCL_OK);
}
