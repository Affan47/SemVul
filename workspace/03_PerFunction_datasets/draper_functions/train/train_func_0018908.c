track_read(int (*cb_func)(time_t timestamp, int status,
			      const char *address, void *voidarg),
	       void *voidarg)
{
	char namebuf[sizeof(TRACKDIR) + NUMBUFSIZE+2];
	char buf2[NUMBUFSIZE];
	FILE *fp;
	time_t curTime=time(NULL) / 3600;
	int i;
	char linebuf[BUFSIZ];
	char *p;

	for (i=0; i <= TRACK_NHOURS; ++i)
	{
		strcat(strcpy(namebuf, TRACKDIR "/"),
		       libmail_str_time_t(curTime - i, buf2));

		if ((fp=fopen(namebuf, "r")) == NULL)
			continue;

		while (fgets(linebuf, sizeof(linebuf), fp))
		{
			p=strchr(linebuf, '\n');
			if (p) *p=0;

			p=strchr(linebuf, ' ');
			if (!p)
				continue;
			++p;

			if (*p)
			{
				int rc=(*cb_func)(libmail_atotime_t(linebuf),
						  *p, p+1, voidarg);

				if (rc)
				{
					fclose(fp);
					return rc;
				}
			}
		}
		fclose(fp);
	}

	return (0);
}
