confbypa(const char *msg, const int code, const struct spptr *pp)
{
	int	begy, y, x;
	WINDOW	*awin;

	getbegyx(pscr, begy, x);
	getyx(pscr, y, x);
	awin = newwin(1, 0, begy + y, 0);
	disp_str = pp->spp_ptr;
	disp_str2 = pp->spp_form;
	wprintw(awin, (char *) msg, pp->spp_ptr);
	wrefresh(awin);
	select_state(code);
	Ew = pscr;

	for  (;;)  {
		do	x = getkey(MAG_A|MAG_P);
		while  (x == EOF);

		if  (hlpscr)  {
			endhe(awin, &hlpscr);
			if  (helpclr)
				continue;
		}
		if  (escr)
			endhe(awin, &escr);

		if  (x == 400)  {
			dochelp(awin, code);
			continue;
		}
		if  (x == 401)  {
			wrefresh(curscr);
			wrefresh(awin);
			continue;
		}
		if  (x == 450  ||  x == 451)
			break;
		doerror(awin, code);
	}
	delwin(awin);
	touchwin(pscr);
	wrefresh(pscr);
	if  (x == 451)
		return 0;
	return  1;
}
