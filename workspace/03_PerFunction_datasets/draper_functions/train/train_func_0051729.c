target_dir(struct keypress ch)
{
	int d = 0;


	if (isdigit((unsigned char)ch.code)) {
		d = D2I(ch.code);
	} else if (isarrow(ch.code)) {
		switch (ch.code) {
			case ARROW_DOWN:  d = 2; break;
			case ARROW_LEFT:  d = 4; break;
			case ARROW_RIGHT: d = 6; break;
			case ARROW_UP:    d = 8; break;
		}
	} else {
		int mode;
		const struct keypress *act;

		if (OPT(rogue_like_commands))
			mode = KEYMAP_MODE_ROGUE;
		else
			mode = KEYMAP_MODE_ORIG;


		act = keymap_find(mode, ch);
		if (act) {
			const struct keypress *cur;
			for (cur = act; cur->type == EVT_KBRD; cur++) {
				if (isdigit((unsigned char) cur->code))
					d = D2I(cur->code);
			}
		}
	}


	if (d == 5) d = 0;


	return (d);
}
