a_unstick(char * opt[]) {
	(void)opt;
	if(!dzen.slave_win.ishmenu
			&& dzen.slave_win.max_lines)
		dzen.slave_win.issticky = False;
	return 0;
}
