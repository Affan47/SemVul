create_transform_from_user(void)
{
    int status;
    int n_points;
    int ok;

    init_transform_arrays();

    n_points = 0;
    ok = 0;
    while (!ok) {
#ifdef __MINGW32__
	G_fatal_error("Points cannot be entered interactively on Windows");
#else

	if ((n_points = ask_transform_coor(n_points)) < 0)
	    exit(-1);
#endif

	G_clear_screen();

	status = setup_transform(n_points);


	if (status != ALL_OK) {
	    G_message(_(" Number of points that have been entered: %d\n"),
		      n_points);
	    print_transform_error(status);
	    continue;
	}

	print_transform_resids(n_points);
	ok = yes_no_quest
	    ("\n\n\nIf satisfied with the residuals, enter 'y', else 'n' and <Return>:  ");

    }


    return (0);

}
