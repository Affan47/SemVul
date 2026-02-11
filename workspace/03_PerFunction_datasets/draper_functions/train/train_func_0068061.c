wherechar(p, wp)
	char *p;
	int *wp;
{
	switch (*p)
	{
	case 'b': case 'd': case 'l': case 'p': case 'P':
		switch (*++p)
		{
		case 't':   *wp = TOP;			break;
		case 'm':   *wp = MIDDLE;		break;
		case 'b':   *wp = BOTTOM;		break;
		case 'B':   *wp = BOTTOM_PLUS_ONE;	break;
		case 'j':   *wp = adjsline(jump_sline);	break;
		default:    *wp = TOP;  p--;		break;
		}
	}
	return (p);
}
