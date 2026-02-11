memget(struct fetchdef *fdef, struct osrel *osrel, struct memstat *mi)
{
	register int	nr, nrfields=7;
	FILE 		*fp;
	char		linebuf[1024];
	char		itsname[32];
	count_t		cnt;

	memset(mi, 0, sizeof(struct memstat));

	if ( (fp = fopen("/proc/meminfo", "r")) == NULL)
		return;

	while ( fgets(linebuf, sizeof(linebuf), fp) != NULL && nrfields > 0)
	{
		nr = sscanf(linebuf, "%s %lld", itsname, &cnt);

		if (nr < 2)
			continue;

		if ( strcmp("MemTotal:", itsname) == EQ)
		{
			mi->memtot = cnt;
			nrfields--;
		}

		if ( strcmp("MemFree:", itsname) == EQ)
		{
			mi->memfree = cnt;
			nrfields--;
		}

		if ( strcmp("Buffers:", itsname) == EQ)
		{
			mi->membuf = cnt;
			nrfields--;
		}

		if ( strcmp("Cached:", itsname) == EQ)
		{
			mi->memcache = cnt;
			nrfields--;
		}

		if ( strcmp("Slab:", itsname) == EQ)
		{
			mi->memslab = cnt;
			nrfields--;
		}

		if ( strcmp("SwapTotal:", itsname) == EQ)
		{
			mi->swptot = cnt;
			nrfields--;
		}

		if ( strcmp("SwapFree:", itsname) == EQ)
		{
			mi->swpfree = cnt;
			nrfields--;
		}
	}

	fclose(fp);
}
