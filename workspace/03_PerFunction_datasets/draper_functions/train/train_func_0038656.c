SitFor(delay)
int	delay;
{
#ifdef MAC
	long
		start,
		end;

	Keyonly = YES;
	redisplay();
	start = Ticks;

	end = start + delay * 6;
	do ; while (!charp() && Ticks < end);

#else

# ifndef MSDOS
	if (!charp()) {
#  ifdef USE_SELECT
		struct timeval	timer;
		fd_set	readfds;


		if (!UpdMesg && !Asking && mesgbuf[0] && !stickymsg)
			message(NullStr);
		redisplay();

		timer.tv_sec = (delay / 10);
		timer.tv_usec = (delay % 10) * 100000;
		FD_ZERO(&readfds);
		FD_SET(0, &readfds);
		(void) select(1,
			&readfds, (fd_set *)NULL, (fd_set *)NULL,
			&timer);
#  else
#   ifdef WIN32
		redisplay();
		inputEventWaiting(delay*100);
#   else

		static const int cps[] = {
			0,
			5,
			7,
			11,
			13,
			15,
			20,
			30,
			60,
			120,
			180,
			240,
			480,
			960,
			1920,
			1920,
		};
		register int	nchars,
				check_cnt;

		nchars = (delay * cps[ospeed]) / 10;
		check_cnt = ScrBufSize;
		redisplay();
		if (!NP) {
			while ((--nchars > 0) && !InputPending) {
				scr_putchar(PC);
				if (--check_cnt == 0) {
					check_cnt = ScrBufSize;
					(void) charp();
				}
			}
		}
#   endif
#  endif
	}
# else


	int	start,
		now,
		end;
	struct dostime_t tc;

	redisplay();
	_dos_gettime(&tc);
	start = tc.second * 100 + tc.hsecond;
	end = start + delay * 10;
	for (;;)  {
		if (charp())
			break;

		_dos_gettime(&tc);
		now = tc.second * 100 + tc.hsecond;
		if (now < start)
			now += 60 * 100;
		if (now >= end)
			break;
	}
# endif
#endif
}
