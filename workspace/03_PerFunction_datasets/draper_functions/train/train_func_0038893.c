skipblob(char *p, char **save_blob_ptr)
{
	char *q;
	char *orig_p=p;
	int isalldigits=1;

	if (*p == '[')
	{
		for (q= p+1; *q; q++)
			if (*q == '[' || *q == ']')
				break;
			else if (strchr("0123456789", *q) == NULL)
				isalldigits=0;

		if (*q == ']')
		{
			p=q+1;

			while (isspace((int)(unsigned char)*p))
			{
				++p;
			}

			if (save_blob_ptr && *save_blob_ptr && !isalldigits)
			{
				while (orig_p != p)
					*(*save_blob_ptr)++=*orig_p++;
			}

			return (p);
		}
	}
	return (p);
}
