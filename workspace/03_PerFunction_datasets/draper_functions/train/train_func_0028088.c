Load()
{
	FILE *f = fopen((const char *)_filename, "r");

	if (f == NULL)
		return -1;

	char buf[MAX_COOKIE_LINE];
	while(fgets(buf, MAX_COOKIE_LINE, f))
	{
		if (*buf && *buf != '#' && (strlen(buf) > 10))
		{
			HtCookie *Cookie = new HtCookie(buf);


			if (!Cookie->GetName().length()
				|| !AddCookieForHost (Cookie, Cookie->GetSrcURL()))
			{
				if (debug > 2)
					cout << "Discarded cookie line: " << buf;
				delete Cookie;
			}

		}
	}

	return 0;

}
