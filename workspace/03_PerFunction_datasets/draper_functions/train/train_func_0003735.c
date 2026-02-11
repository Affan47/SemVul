serialPOS_cursor_goto(Driver *drvthis, int x, int y)
{
	PrivateData *p = drvthis->private_data;
	unsigned int length = 8;
	char out[length];

	switch ((int)p->emulation_mode) {
		case POS_Epson:
			length = 7;

			snprintf(out, length, "%c%c%02d%02d", 0x1F, 0x24, x, y);
			break;

		case POS_LogicControls:
			length = 4;

			snprintf(out, length, "%c%02d", 0x10, (x-1+((y-1)*(p->width))));
			break;

		default:
			return;
	}

	write(p->fd, out, length);
}
