resume_curses(quietly)
	int	quietly;
{
	if (!curses_active)
	{

#if ANY_UNIX
# if UNIXV
		ospeed = cfgetospeed(&oldtermio);
		ERASEKEY = oldtermio.c_cc[VERASE];
		newtermio = oldtermio;
		newtermio.c_iflag &= (IXON|IXOFF|IXANY|ISTRIP|IGNBRK);
		newtermio.c_oflag &= ~OPOST;
		newtermio.c_lflag &= ISIG;
		newtermio.c_cc[VINTR] = ctrl('C');
#ifdef VSUSP
		newtermio.c_cc[VSUSP] = 0;
#endif
#ifdef VLNEXT
		newtermio.c_cc[VLNEXT] = 0;
#endif
		newtermio.c_cc[VMIN] = 1;
		newtermio.c_cc[VTIME] = 0;
#  ifdef VSWTCH
		newtermio.c_cc[VSWTCH] = 0;
#  endif
		tcsetattr(2, TCSANOW, &newtermio);
# else
		struct tchars	tbuf;
#  ifdef TIOCSLTC
		struct ltchars	ltbuf;
#  endif

		ospeed = oldsgttyb.sg_ospeed;
		ERASEKEY = oldsgttyb.sg_erase;
		newsgttyb = oldsgttyb;
		newsgttyb.sg_flags |= CBREAK;
		newsgttyb.sg_flags &= ~(CRMOD|ECHO|XTABS);
		ioctl(2, TIOCSETP, &newsgttyb);

		ioctl(2, TIOCGETC, &tbuf);
		oldint = tbuf.t_intrc;
		tbuf.t_intrc = ctrl('C');
		ioctl(2, TIOCSETC, &tbuf);

#  ifdef TIOCSLTC
		ioctl(2, TIOCGLTC, &ltbuf);
		oldswitch = ltbuf.t_suspc;
		ltbuf.t_suspc = 0;
		oldquote = ltbuf.t_lnextc;
		ltbuf.t_lnextc = 0;
		ioctl(2, TIOCSLTC, &ltbuf);
#  endif

# endif
#endif
#if OSK
		newsgttyb = oldsgttyb;
		newsgttyb.sg_echo = 0;
		newsgttyb.sg_eofch = 0;
		newsgttyb.sg_kbach = 0;
		newsgttyb.sg_kbich = ctrl('C');
		_ss_opt(0, &newsgttyb);
		ospeed = oldsgttyb.sg_baud;
		ERASEKEY = oldsgttyb.sg_bspch;
#endif

		if (has_TI)
		{
			do_TI();
		}
		if (has_KS)
		{
			do_KS();
		}

		curses_active = TRUE;
	}


	if (quietly)
	{
		return;
	}

	signal(SIGINT, SIG_IGN);

	move(LINES - 1, 0);
	do_SO();
	qaddstr("[Press <RETURN> to continue]");
	do_SE();
	refresh();
	ttyread(kbuf, 20);
	if (kbuf[0] == ':')
	{
		mode = MODE_COLON;
		addch('\n');
		refresh();
	}
	else
	{
		mode = MODE_VI;
		redraw(MARK_UNSET, FALSE);
	}
	exwrote = FALSE;

#if TURBOC
	signal(SIGINT, (void(*)()) trapint);
#else
	signal(SIGINT, trapint);
#endif
}
