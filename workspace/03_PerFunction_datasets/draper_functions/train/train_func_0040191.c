maildir_info_imapmunge(const char *name)
{
	char *n=libmail_u_convert_tobuf(name, "utf8",
					unicode_x_imap_modutf7, NULL);
	char *p;
	size_t cnt;

	if (!n)
		return NULL;

	if (!complex_flag)
	{
		for (p=n; *p; p++)
		{
			if (*p == '.' || *p == '/')
				*p=' ';
		}

		return n;
	}

	cnt=munge_complex(n, NULL);
	p=malloc(cnt);
	if (!p)
	{
		free(n);
		return NULL;
	}

	munge_complex(n, p);

	free(n);
	return p;
}
