set_frame(double *msc, int *t, int *b, int *l, int *r)
{
    int t0, b0, l0, r0, btn;


    t0 = *t;
    b0 = *b;
    l0 = *l;
    r0 = *r;


    G_system("clear");

    if (G_yes
	("\n    Will the sampling frame (total area within which sampling\n      units are distributed) be the whole map?   ",
	 1)) {
	R_open_driver();
	R_standard_color(D_translate_color("grey"));
	draw_box(*l, *t, *r, *b, 1);
	R_close_driver();
	fprintf(stderr, "\n    Sampling frame set to whole map");
    }


    else {
      back:
	G_system("clear");
	fprintf(stderr, " \n    OUTLINE SAMPLING FRAME:\n");
	R_open_driver();
	fprintf(stderr,
		"\n    Please move cursor to the UPPER-LEFT corner of\n");
	fprintf(stderr,
		"       the sampling frame and click any mouse button\n");
	R_get_location_with_line(0, 0, l, t, &btn);

	fprintf(stderr,
		"\n    Please move cursor to the LOWER-RIGHT corner of\n");
	fprintf(stderr,
		"       the sampling frame and click any mouse button again\n");
      back2:
	R_get_location_with_box(*l, *t, r, b, &btn);


	if (*l < l0 || *r > r0 || *t < t0 || *b > b0) {
	    fprintf(stderr,
		    "\n    The cursor is outside of the map, try again\n");
	    goto back;
	}


	if (*r <= *l || *b <= *t) {
	    fprintf(stderr,
		    "\n    Please put the lower right corner below and to the");
	    fprintf(stderr, "\n    right of the upper left corner\n");
	    goto back2;
	}

	R_standard_color(D_translate_color("grey"));
	*l = (int)((double)((int)(*l * msc[0] + 0.5)) / msc[0]);
	*r = (int)((double)((int)(*r * msc[0] + 0.5)) / msc[0]);
	*t = (int)((double)((int)(*t * msc[1] + 0.5)) / msc[1]);
	*b = (int)((double)((int)(*b * msc[1] + 0.5)) / msc[1]);
	draw_box(*l, *t, *r, *b, 1);
	R_close_driver();
	fprintf(stderr,
		"\n    Sampling frame is set to the area you just drew");
    }
    return;
}
