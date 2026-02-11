EscStatusLine(u_char mode)
{
    static struct attrStack *asp;

    switch(mode) {
    case 'T':
	if (con.sl == SL_ENTER) break;
	if (!asp) SaveAttr(&asp);
    case 'S':
	if (con.sl == SL_NONE) {
	    con.ymax = dInfo.tymax - 1;
	    SetWinSize();
	}
	if (mode == 'T') {
	    con.sl = SL_ENTER;
	    SetRegion(dInfo.tymax, dInfo.tymax);
	}
	break;
    case 'F':
	if (con.sl == SL_ENTER) {
	    con.sl = SL_LEAVE;
	    SetRegion(0, dInfo.tymax - 1);
	    if (asp) RestoreAttr(asp);
	    asp = NULL;
	}
	break;
    case 'H':
    case 'E':
	if (con.sl == SL_NONE) break;
	SetRegion(0, dInfo.tymax);
	SetWinSize();
	con.sl = SL_NONE;
	break;
    default:
	con.esc = EscBracket;
	EscBracket(mode);
	return;
    }
    con.wrap = FALSE;
    con.esc = NULL;
}
