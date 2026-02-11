getdw(WINDOW *w, const int row, const int acol)
{
	int	col, ch, err_no;

	col = tcp.wd_col;

	for  (;;)  {
		wmove(w, row, col);
		wrefresh(w);

		do  ch = getkey(MAG_P|MAG_A);
		while  (ch == EOF  &&  (hlpscr || escr));
		if  (hlpscr)  {
			endhe(w, &hlpscr);
			if  (helpclr)
				continue;
		}
		if  (escr)
			endhe(w, &escr);

		switch  (ch)  {
		case  EOF:
			continue;
		default:
			err_no = 452;
		err:
			doerror(w, err_no);
			continue;

		case  400:
			dochelp(w, 452);
			continue;

		case  401:
			wrefresh(curscr);
			continue;

		case  402:
			return  0;

		case  404:
		case  406:
		case  407:
		case  405:
		case  420:
			if  ((time_t) JREQ.spq_hold > time((time_t *) 0))
				return  ch;
			err_no = 447;
			goto  err;

		case  551:
			JREQ.spq_hold = 0;
			tdisplay(w, (time_t) JREQ.spq_hold, row, acol);
			return  404;

		case  422:
		case  423:
			return  ch;

		case  552:
			JREQ.spq_hold += SECSPERDAY;
			tdisplay(w, (time_t) JREQ.spq_hold, row, acol);
			continue;

		case  553:
			JREQ.spq_hold -= SECSPERDAY;
			tdisplay(w, (time_t) JREQ.spq_hold, row, acol);
			continue;
		}
	}
}
