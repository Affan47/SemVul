CONF_parse_list(const char *list_, int sep, int nospc,
	int (*list_cb)(const char *elem, int len, void *usr), void *arg)
	{
	int ret;
	const char *lstart, *tmpend, *p;

	if(list_ == NULL)
		{
		CONFerr(CONF_F_CONF_PARSE_LIST, CONF_R_LIST_CANNOT_BE_NULL);
		return 0;
		}

	lstart = list_;
	for(;;)
		{
		if (nospc)
			{
			while(*lstart && isspace((unsigned char)*lstart))
				lstart++;
			}
		p = strchr(lstart, sep);
		if (p == lstart || !*lstart)
			ret = list_cb(NULL, 0, arg);
		else
			{
			if (p)
				tmpend = p - 1;
			else
				tmpend = lstart + strlen(lstart) - 1;
			if (nospc)
				{
				while(isspace((unsigned char)*tmpend))
					tmpend--;
				}
			ret = list_cb(lstart, tmpend - lstart + 1, arg);
			}
		if (ret <= 0)
			return ret;
		if (p == NULL)
			return 1;
		lstart = p + 1;
		}
	}
