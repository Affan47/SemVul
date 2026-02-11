v4l_key_command(rfbBool down, rfbKeySym keysym, rfbClientPtr client) {
	allowed_input_t input;

	if (raw_fb_fd < 0) {
		return;
	}
	if (! down) {
		return;
	}
	if (view_only) {
		return;
	}
	get_allowed_input(client, &input);
	if (! input.keystroke) {
		return;
	}

	if (keysym == XK_b) {
		v4l_br(-1);
	} else if (keysym == XK_B) {
		v4l_br(+1);
	} else if (keysym == XK_h) {
		v4l_hu(-1);
	} else if (keysym == XK_H) {
		v4l_hu(+1);
	} else if (keysym == XK_c) {
		v4l_co(-1);
	} else if (keysym == XK_C) {
		v4l_co(+1);
	} else if (keysym == XK_n) {
		v4l_cn(-1);
	} else if (keysym == XK_N) {
		v4l_cn(+1);
	} else if (keysym == XK_s) {
		v4l_sz(-1);
	} else if (keysym == XK_S) {
		v4l_sz(+1);
	} else if (keysym == XK_i) {
		v4l_inp(-1);
	} else if (keysym == XK_I) {
		v4l_inp(-2);
	} else if (keysym == XK_Up) {
		v4l_sta(+0);
	} else if (keysym == XK_Down) {
		v4l_sta(-1);
	} else if (keysym == XK_F1) {
		v4l_fmt("HI240");
	} else if (keysym == XK_F2) {
		v4l_fmt("RGB565");
	} else if (keysym == XK_F3) {
		v4l_fmt("RGB24");
	} else if (keysym == XK_F4) {
		v4l_fmt("RGB32");
	} else if (keysym == XK_F5) {
		v4l_fmt("RGB555");
	} else if (keysym == XK_F6) {
		v4l_fmt("GREY");
	}
	if (client) {}
}
