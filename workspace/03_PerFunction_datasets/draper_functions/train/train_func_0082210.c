MtxOrb_cursor (Driver *drvthis, int x, int y, int state)
{
	PrivateData *p = (PrivateData *) drvthis->private_data;


	switch (state) {
		case CURSOR_OFF:
			write(p->fd, "\xFE" "K", 2);
			break;
		case CURSOR_UNDER:
		case CURSOR_BLOCK:
		case CURSOR_DEFAULT_ON:
		default:
			write(p->fd, "\xFE" "J", 2);
			break;
	}


	 MtxOrb_cursor_goto(drvthis, x, y);
}
