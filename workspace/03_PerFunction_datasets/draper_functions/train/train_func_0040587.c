readnewevent_callback(char *p, int n, void *vp)
{
	struct readnewevent_s *rne=(struct readnewevent_s *)vp;
	int cnt=0;

	if (!rne->sentprompt)
	{
		rne->sentprompt=1;
		printf("300 Send event text, terminate by a line with a single dot.\n");
	}

	while (!rne->seeneof && n)
	{
		int c=inputchar(rne->pcp);

		if (c == EOF)
		{
			rne->seeneof=1;
			errno=ETIMEDOUT;
			return (-1);
		}

		if (c == '\r')
			continue;

		if (c == '\n')
		{
			if (rne->seendot)
				rne->seeneof=1;
			rne->seendot=0;
			rne->seeneol=1;
			if (rne->seeneof)
				continue;
		}
		else
		{
			rne->seendot= c == '.' && rne->seeneol;
			rne->seeneol=0;
			if (rne->seendot)
				continue;
		}
		putc(c, rne->tmpfile);
		++cnt;
		*p++ = c;
		--n;

		if (++rne->cnt >= 8192)
		{
			time_t t;

			time(&t);
			if (t >= rne->last_noop_time+300)
			{
				struct proxy_list *p;
				rne->last_noop_time=t;
				for (p=proxy_list; p; p=p->next)
					pcp_noop(p->proxy);
			}

			pcpdtimer_install(&rne->inactivity_timeout, 300);
			rne->cnt=0;
		}
	}
	return (cnt);
}
