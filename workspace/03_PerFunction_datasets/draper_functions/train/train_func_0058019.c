set_nofb_params(int restore) {
	static int first = 1;
	static int save[100];
	static char *scroll = NULL;
	int i = 0;

	if (first) {
		first = 0;
		save[i++] = use_xfixes;
		save[i++] = use_xdamage;
		save[i++] = use_xrecord;
		save[i++] = wireframe;
		save[i++] = use_solid_bg;
		save[i++] = overlay;
		save[i++] = overlay_cursor;
		save[i++] = using_shm;
		save[i++] = single_copytile;
		save[i++] = take_naps;
		save[i++] = measure_speeds;
		save[i++] = grab_buster;
		save[i++] = show_cursor;
		save[i++] = cursor_shape_updates;
		save[i++] = cursor_pos_updates;
		save[i++] = ncache;

		scroll = scroll_copyrect;
	}
	if (restore) {
		i = 0;
		use_xfixes            = save[i++];
		use_xdamage           = save[i++];
		use_xrecord           = save[i++];
		wireframe             = save[i++];
		use_solid_bg          = save[i++];
		overlay               = save[i++];
		overlay_cursor        = save[i++];
		using_shm             = save[i++];
		single_copytile       = save[i++];
		take_naps             = save[i++];
		measure_speeds        = save[i++];
		grab_buster           = save[i++];
		show_cursor           = save[i++];
		cursor_shape_updates  = save[i++];
		cursor_pos_updates    = save[i++];
		ncache                = save[i++];

		scroll_copyrect = scroll;

		if (cursor_shape_updates) {
			restore_cursor_shape_updates(screen);
		}
		initialize_cursors_mode();

		return;
	}

	use_xfixes = 0;
	use_xdamage = 0;
	use_xrecord = 0;
	wireframe = 0;

	use_solid_bg = 0;
	overlay = 0;
	overlay_cursor = 0;

	using_shm = 0;
	single_copytile = 1;

	take_naps = 0;
	measure_speeds = 0;


	grab_buster = 0;

	show_cursor = 0;
	show_multiple_cursors = 0;
	cursor_shape_updates = 0;
	if (! got_cursorpos) {
		cursor_pos_updates = 0;
	}

	ncache = 0;

	scroll_copyrect = "never";

	if (! quiet) {
		rfbLog("disabling: xfixes, xdamage, solid, overlay, shm,\n");
		rfbLog("  wireframe, scrollcopyrect, ncache,\n");
		rfbLog("  noonetile, nap, cursor, %scursorshape\n",
		    got_cursorpos ? "" : "cursorpos, " );
		rfbLog("  in -nofb mode.\n");
	}
}
