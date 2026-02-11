SIG_deregister(int sig, RETSIGTYPE (*fn)())
{
	int			val;
	struct SIG_hlist	*this;
	struct SIG_hlist	*last;
#ifdef POSIX_SIGNALS
	sigset_t		sigset_mask, sigset_omask;
#else
#ifdef BSD_SIGNALS
	int			mask;
#endif
#endif


	if (SIG_init() != 0)
		return (-1);
	val = 0;
	last = (struct SIG_hlist *) NULL;


#ifdef POSIX_SIGNALS
	(void) sigemptyset(&sigset_mask);
	(void) sigaddset(&sigset_mask, sig);
	(void) sigprocmask(SIG_BLOCK, &sigset_mask, &sigset_omask);
#else
#ifdef BSD_SIGNALS
	mask = sigblock(sigmask(sig));
#endif
#endif


	this = SIG_handlers[sig];
	while ((this != (struct SIG_hlist *) NULL) && (this->handler != fn))
	{
		last = this;
		this = this->next;
	}


	if (this != (struct SIG_hlist *) NULL)
	{
		if (last == (struct SIG_hlist *) NULL)
		{
			SIG_handlers[sig] = this->next;
		}
		else
		{
			last->next = this->next;
		}
		free((char *) this);
	}


	if (SIG_handlers[sig] == (struct SIG_hlist *) NULL)
	{
#ifdef POSIX_SIGNALS
		val = sigaction(sig, &SIG_defaults[sig],
				(struct sigaction *) NULL);
#else
#ifdef BSD_SIGNALS
		val = sigvec(sig, &SIG_defaults[sig], (struct sigvec *) NULL);
#else
		if (signal(sig, SIG_defaults[sig]) == SIG_ERR)
			val = -1;
#endif
#endif
	}


#ifdef POSIX_SIGNALS
	(void) sigprocmask(SIG_SETMASK, &sigset_omask, NULL);
#else
#ifdef BSD_SIGNALS
	(void) sigsetmask(mask);
#endif
#endif

	return val;
}
