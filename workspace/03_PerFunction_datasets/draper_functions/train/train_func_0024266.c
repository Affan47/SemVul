cycle_colors(int ch, int *fg, int *bg, short *pair)
{
    bool result = FALSE;

    if (use_colors) {
	result = TRUE;
	switch (ch) {
	case 'F':
	    if ((*fg -= 1) < 0)
		*fg = COLORS - 1;
	    break;
	case 'f':
	    if ((*fg += 1) >= COLORS)
		*fg = 0;
	    break;
	case 'B':
	    if ((*bg -= 1) < 0)
		*bg = COLORS - 1;
	    break;
	case 'b':
	    if ((*bg += 1) >= COLORS)
		*bg = 0;
	    break;
	default:
	    result = FALSE;
	    break;
	}
	if (result) {
	    *pair = (short) (*fg != COLOR_BLACK || *bg != COLOR_BLACK);
	    if (*pair != 0) {
		*pair = 1;
		if (init_pair(*pair, (short) *fg, (short) *bg) == ERR) {
		    result = FALSE;
		}
	    }
	}
    }
    return result;
}
