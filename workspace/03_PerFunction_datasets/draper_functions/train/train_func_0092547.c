reset_drawing (void)
{
	unsigned int i;

	max_diwstop = 0;

	lores_reset ();

	for (i = 0; i < sizeof linestate / sizeof *linestate; i++)
		linestate[i] = LINE_UNDECIDED;

	init_aspect_maps ();

	init_row_map ();

	last_redraw_point = 0;

	memset (spixels, 0, sizeof spixels);
	memset (&spixstate, 0, sizeof spixstate);

	init_drawing_frame ();

	notice_screen_contents_lost ();
	frame_res_cnt = FRAMES_UNTIL_RES_SWITCH;
	lightpen_y1 = lightpen_y2 = -1;

	reset_custom_limits ();

	clearbuffer (&gfxvidinfo.drawbuffer);
	clearbuffer (&gfxvidinfo.tempbuffer);

	center_reset = true;
	specialmonitoron = false;
}
