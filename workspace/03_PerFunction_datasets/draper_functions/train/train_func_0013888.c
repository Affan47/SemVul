check_user_input(double dt, double dtr, int tile_diffs, int *cnt) {

	if (rawfb_vnc_reflect) {
		if (got_user_input) {
			if (0) vnc_reflect_process_client();
		}
		if (got_user_input && *cnt % ui_skip != 0) {

			*cnt = *cnt + 1;
			return 1;
		}
	}
#ifdef MACOSX
	if (! macosx_console) {
		RAWFB_RET(0)
	}
#else
	RAWFB_RET(0)
#endif

	if (use_xrecord) {
		int rc = check_xrecord();


if (debug_scroll && rc > 1) fprintf(stderr, "  CXR: check_user_input ret %d\n", rc - 1);
		if (rc == 0) {
			;
		} else {
			return rc - 1;
		}
	}

	if (wireframe) {
		if (check_wireframe()) {
			return 0;
		}
	}

	if (pointer_mode == 1) {
		if ((got_user_input || ui_skip < 0) && *cnt % ui_skip != 0) {

			*cnt = *cnt + 1;
			X_LOCK;
			XFlush_wr(dpy);
			X_UNLOCK;
			return 1;
		} else {
			return 0;
		}
	}
	if (pointer_mode >= 2 && pointer_mode <= 4) {
		if (got_keyboard_input) {


			if (*cnt % ui_skip != 0) {
				*cnt = *cnt + 1;
				return 1;
			}
		}

	}

	if (pointer_mode == 2) {
		check_user_input2(dt);
	} else if (pointer_mode == 3) {
		check_user_input3(dt, dtr, tile_diffs);
	} else if (pointer_mode == 4) {
		check_user_input4(dt, dtr, tile_diffs);
	}
	return 0;
}
