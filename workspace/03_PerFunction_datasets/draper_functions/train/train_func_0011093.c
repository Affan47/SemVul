t_warn(struct rm *lev)
{
    static const char warn_str[] = "wall_angle: %s: case %d: seenv = 0x%x";
    const char *wname;

    if (lev->typ == TUWALL) wname = "tuwall";
    else if (lev->typ == TLWALL) wname = "tlwall";
    else if (lev->typ == TRWALL) wname = "trwall";
    else if (lev->typ == TDWALL) wname = "tdwall";
    else wname = "unknown";
    impossible(warn_str, wname, lev->wall_info & WM_MASK,
	(unsigned int) lev->seenv);
}
