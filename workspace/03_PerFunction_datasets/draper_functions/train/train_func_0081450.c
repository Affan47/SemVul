tty_askname(void)
{
    static char who_are_you[] = "Who are you? ";
    register int c, ct, tryct = 0;

    tty_putstr(BASE_WINDOW, 0, "");
    do {
	if (++tryct > 1) {
	    if (tryct > 10) bail("Giving up after 10 tries.\n");
	    tty_curs(BASE_WINDOW, 1, wins[BASE_WINDOW]->cury - 1);
	    tty_putstr(BASE_WINDOW, 0, "Enter a name for your character...");

	    tty_curs(BASE_WINDOW, 1, wins[BASE_WINDOW]->cury),  cl_end();
	}
	tty_putstr(BASE_WINDOW, 0, who_are_you);
	tty_curs(BASE_WINDOW, (int)(sizeof who_are_you),
		 wins[BASE_WINDOW]->cury - 1);
	ct = 0;
	while((c = tty_nhgetch()) != '\n') {
		if(c == EOF) error("End of input\n");
		if (c == '\033') { ct = 0; break; }
#if defined(WIN32CON)
		if (c == '\003') bail("^C abort.\n");
#endif

		if (c == '\b' || c == '\177') {
			if(ct) {
				ct--;
#ifdef WIN32CON
				ttyDisplay->curx--;
#endif
#if defined(MICRO) || defined(WIN32CON)
# if defined(WIN32CON)
				backsp();
				putchar(' ');
				backsp();
# else
				msmsg("\b \b");
# endif
#else
				putchar('\b');
				putchar(' ');
				putchar('\b');
#endif
			}
			continue;
		}
#if defined(UNIX) || defined(VMS)
		if(c != '-' && c != '@')
		if(c < 'A' || (c > 'Z' && c < 'a') || c > 'z') c = '_';
#endif
		if (ct < (int)(sizeof plname) - 1) {
#if defined(MICRO)
			msmsg("%c", c);
#else
			putchar(c);
#endif
			plname[ct++] = c;
#ifdef WIN32CON
			ttyDisplay->curx++;
#endif
		}
	}
	plname[ct] = 0;
    } while (ct == 0);


    tty_curs(BASE_WINDOW, 1, wins[BASE_WINDOW]->cury + 1);
}
