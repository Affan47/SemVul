trackpoint_toggle_bit(struct ps2dev *ps2dev,
				 unsigned char loc, unsigned char mask)
{

	if (loc < 0x20 || loc >= 0x2F)
		return -1;

	if (ps2_command(ps2dev, NULL, MAKE_PS2_CMD(0, 0, TP_COMMAND)) ||
	    ps2_command(ps2dev, NULL, MAKE_PS2_CMD(0, 0, TP_TOGGLE)) ||
	    ps2_command(ps2dev, NULL, MAKE_PS2_CMD(0, 0, loc)) ||
	    ps2_command(ps2dev, NULL, MAKE_PS2_CMD(0, 0, mask))) {
		return -1;
	}

	return 0;
}
