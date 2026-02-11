mch_settmode(tmode)
    int		tmode;
{
    static int first = TRUE;


#if defined(ECHOE) && defined(ICANON) && (defined(HAVE_TERMIO_H) || defined(HAVE_TERMIOS_H)) && !defined(__NeXT__)


# ifdef HAVE_TERMIOS_H
    static struct termios told;
	   struct termios tnew;
# else
    static struct termio told;
	   struct termio tnew;
# endif

    if (first)
    {
	first = FALSE;
# if defined(HAVE_TERMIOS_H)
	tcgetattr(read_cmd_fd, &told);
# else
	ioctl(read_cmd_fd, TCGETA, &told);
# endif
    }

    tnew = told;
    if (tmode == TMODE_RAW)
    {


	tnew.c_iflag &= ~ICRNL;
	tnew.c_lflag &= ~(ICANON | ECHO | ISIG | ECHOE
# if defined(IEXTEN) && !defined(__MINT__)
		    | IEXTEN

# endif
				);
# ifdef ONLCR
	tnew.c_oflag &= ~ONLCR;
# endif
	tnew.c_cc[VMIN] = 1;
	tnew.c_cc[VTIME] = 0;
    }
    else if (tmode == TMODE_SLEEP)
	tnew.c_lflag &= ~(ECHO);

# if defined(HAVE_TERMIOS_H)
    {
	int	n = 10;


	while (tcsetattr(read_cmd_fd, TCSANOW, &tnew) == -1
						   && errno == EINTR && n > 0)
	    --n;
    }
# else
    ioctl(read_cmd_fd, TCSETA, &tnew);
# endif

#else


# ifndef TIOCSETN
#  define TIOCSETN TIOCSETP
# endif
    static struct sgttyb ttybold;
	   struct sgttyb ttybnew;

    if (first)
    {
	first = FALSE;
	ioctl(read_cmd_fd, TIOCGETP, &ttybold);
    }

    ttybnew = ttybold;
    if (tmode == TMODE_RAW)
    {
	ttybnew.sg_flags &= ~(CRMOD | ECHO);
	ttybnew.sg_flags |= RAW;
    }
    else if (tmode == TMODE_SLEEP)
	ttybnew.sg_flags &= ~(ECHO);
    ioctl(read_cmd_fd, TIOCSETN, &ttybnew);
#endif
    curr_tmode = tmode;
}
