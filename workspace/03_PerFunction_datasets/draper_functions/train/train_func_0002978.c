passwd(int fd, char *prebuf)
{
	char *p;
	const char *service;
	const char *userid;
	const char *opwd;
	const char *npwd;

	for (p=prebuf; *p; p++)
	{
		if (*p == '\t')
			continue;
		if ((int)(unsigned char)*p < ' ')
		{
			writeauth(fd, "FAIL\n", 5);
			return;
		}
	}

	service=prebuf;

	if ((p=strchr(service, '\t')) != 0)
	{
		*p++=0;
		userid=p;
		if ((p=strchr(p, '\t')) != 0)
		{
			*p++=0;
			opwd=p;
			if ((p=strchr(p, '\t')) != 0)
			{
				*p++=0;
				npwd=p;
				if ((p=strchr(p, '\t')) != 0)
					*p=0;
				dopasswd(fd, service, userid, opwd, npwd);
				return;
			}
		}
	}
}
