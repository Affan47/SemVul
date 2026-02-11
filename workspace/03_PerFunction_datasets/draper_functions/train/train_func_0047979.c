initialize_pointer_map(char *pointer_remap) {
	unsigned char map[MAX_BUTTONS];
	int i, k;


	if (!raw_fb_str) {
#if NO_X11
		num_buttons = 5;
#else
		X_LOCK;
		num_buttons = XGetPointerMapping(dpy, map, MAX_BUTTONS);
		X_UNLOCK;
		rfbLog("The X server says there are %d mouse buttons.\n", num_buttons);
#endif
	} else {
		num_buttons = 5;
		rfbLog("Manually set num_buttons to: %d\n", num_buttons);
	}

	if (num_buttons < 0) {
		num_buttons = 0;
	}


	for (i=1; i<= MAX_BUTTONS; i++) {
		for (k=0; k < MAX_BUTTON_EVENTS; k++) {
			pointer_map[i][k].end = 1;
		}
		pointer_map[i][0].keysym  = NoSymbol;
		pointer_map[i][0].keycode = NoSymbol;
		pointer_map[i][0].button = i;
		pointer_map[i][0].end    = 0;
		pointer_map[i][0].down   = 0;
		pointer_map[i][0].up     = 0;
	}

	if (pointer_remap && *pointer_remap != '\0') {

		char *p, *q, *remap = strdup(pointer_remap);
		int n;

		if ((p = strchr(remap, '=')) != NULL) {

			n = atoi(p+1);
			*p = '\0';
			if (n < num_buttons || num_buttons == 0) {
				num_buttons = n;
			} else {
				rfbLog("warning: increasing number of mouse "
				    "buttons from %d to %d\n", num_buttons, n);
				num_buttons = n;
			}
		}
		if ((q = strchr(remap, '-')) != NULL) {


			char str[2];
			int from;

			rfbLog("remapping pointer buttons using string:\n");
			rfbLog("   \"%s\"\n", remap);

			p = remap;
			q++;
			i = 0;
			str[1] = '\0';
			while (*p != '-') {
				str[0] = *p;
				from = atoi(str);
				buttonparse(from, &q);
				p++;
			}
		}
		free(remap);
	}
}
