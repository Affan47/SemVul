parseAlign(char *s, xdot_align * ap)
{
    int i;
    s = parseInt(s, &i);

    if (i < 0)
	*ap = xd_left;
    else if (i > 0)
	*ap = xd_right;
    else
	*ap = xd_center;
    return s;
}
