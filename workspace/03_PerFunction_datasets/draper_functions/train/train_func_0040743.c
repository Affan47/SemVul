help(void)
{
	WINDOW *win;
	PANEL  *pan;
	int     h;
   int     w;
	char   *t;
	char   *b;
	int     n;
	int     done;

   w = 37;
   h = 12;
	n = 0;
	t = " HELP ";
   b = " Press 'Q' to quit ";

	if ((win = newwin(h, w, ((LINES - h) / 2), ((COLS - w) / 2))))
	{
		if ((pan = new_panel(win)))
		{
			set_window_background(win, color(11));
			wattrset(win, color(12));
			box(win, ACS_VLINE, ACS_HLINE);

			mvwprintw(win,       0, ((w - strlen(t)) / 2), "%s", t);
			mvwprintw(win, (h - 1), ((w - strlen(b)) / 2), "%s", b);

			wattrset(win, color(11));

			mvwprintw(win,  2, 3, "RETURN             Play message");
			mvwprintw(win,  3, 3, "R           Reload message list");
			mvwprintw(win,  4, 3, "N            Toggle read/unread");
			mvwprintw(win,  5, 3, "D        Toggle delete/undelete");
			mvwprintw(win,  6, 3, "S                Status control");
			mvwprintw(win,  7, 3, "I           Message information");
			mvwprintw(win,  8, 3, "+/-                  Volume +/-");
			mvwprintw(win,  9, 3, "Q                     Quit vbox");

			update_panels();
			wrefresh(win);
			move((LINES - 2), 0);

			cbreak();
			noecho();
			wtimeout(win, 1000);

			done = FALSE;

			while (!done)
			{
				switch (wgetch(win))
				{
					case ERR:
						if (++n > 30)
						{
							vboxd_put_message("NOOP");

							n = 0;
						}
						break;

					case 'Q':
					case 'q':
						done = TRUE;
						break;
				}
			}

			del_panel(pan);
		}

		delwin(win);
	}
}
