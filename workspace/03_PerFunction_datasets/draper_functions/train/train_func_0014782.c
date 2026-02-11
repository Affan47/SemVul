open_calendar(const char *p)
{
        struct PCP *pcp;
        struct passwd *pw=getpwuid(getuid());
        const char *cp;

        if (!pw)
        {
                perror("getpwuid");
                exit(1);
        }

	userid=strdup(pw->pw_name);

        if (p && *p)
	{
		if (chdir(p))
		{
			perror(p);
			exit(1);
		}
	}
        else if ((cp=getenv("PCPDIR")) != NULL && *cp)
        {
		if (chdir(cp))
		{
			perror(cp);
			exit(1);
		}
        }

	pcp=pcp_open_dir(".", userid);

	if (pcp && pcp_cleanup(pcp))
	{
		pcp_close(pcp);
		pcp=NULL;
	}

	if (!pcp)
	{
		perror("pcp_open_dir");
		exit(1);
	}
	return (pcp);
}
