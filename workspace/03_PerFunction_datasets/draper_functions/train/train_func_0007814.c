Term_xtra_gtk(int n, int v)
{

	switch (n)
	{

		case TERM_XTRA_NOISE:
			return (0);


		case TERM_XTRA_FRESH:
			return (Term_fresh_gtk());


		case TERM_XTRA_BORED:
			return (CheckEvent(0));


		case TERM_XTRA_EVENT:
			return (CheckEvent(v));


		case TERM_XTRA_FLUSH:
			return (Term_flush_gtk());


		case TERM_XTRA_LEVEL:
			return (0);


		case TERM_XTRA_CLEAR:
			return (Term_clear_gtk());


		case TERM_XTRA_DELAY:
			if (v > 0) usleep(1000 * v);
			return (0);


		case TERM_XTRA_REACT:
			return (0);
	}


	return (1);
}
