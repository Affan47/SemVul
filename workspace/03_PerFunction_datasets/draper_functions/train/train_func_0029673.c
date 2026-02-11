savekeys(fd)
	int	fd;
{
	int	i;
	char	buf[80];


	for (i = 0; i < MAXMAPS; i++)
	{

		if (mapped[i].name)
		{
			continue;
		}


		if (mapped[i].len <= 0)
		{
			continue;
		}


#ifndef NO_EXTENSIONS
		if (mapped[i].when & WHEN_INMV)
		{
#if OSK
			char	fmt[80];
			sprintf(fmt, "map%%s %%.%ds %%s\n", mapped[i].len);
			sprintf(buf, fmt,
				(mapped[i].when & WHEN_VICMD) ? "" : "!",
#else
			sprintf(buf, "map%s %.*s visual %s\n",
				(mapped[i].when & WHEN_VICMD) ? "" : "!",
				mapped[i].len,
#endif
				mapped[i].rawin,
				mapped[i].cooked);
			twrite(fd, buf, strlen(buf));
		}
		else
#endif
		{
			if (mapped[i].when & WHEN_VICMD)
			{
#if OSK
				char	fmt[80];
				sprintf(fmt, "map %%.%ds %%s\n", mapped[i].len);
				sprintf(buf, fmt,
#else
				sprintf(buf, "map %.*s %s\n", mapped[i].len,
#endif
					mapped[i].rawin,
					mapped[i].cooked);
				twrite(fd, buf, strlen(buf));
			}
			if (mapped[i].when & (WHEN_VIINP | WHEN_VIREP))
			{
#if OSK
				char	fmt[80];
				sprintf(fmt, "map! %%.%ds %%s\n", mapped[i].len);
				sprintf(buf, fmt,
#else
				sprintf(buf, "map! %.*s %s\n", mapped[i].len,
#endif
					mapped[i].rawin,
					mapped[i].cooked);
				twrite(fd, buf, strlen(buf));
			}
		}
	}
}
