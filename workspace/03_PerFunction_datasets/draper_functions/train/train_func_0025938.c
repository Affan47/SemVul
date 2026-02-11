resettermattr(w)
int w;
{
	if (w >= 0) {
		pty[w].cur.attr = (u_short)0;
		pty[w].cur.fg = pty[w].cur.bg = (short)-1;
	}
	else if (last_attr || last_fg >= (short)0 || last_bg >= (short)0) {
		putterm(T_NORMAL);
		last_attr = (u_short)0;
		last_fg = last_bg = (short)-1;
	}
}
