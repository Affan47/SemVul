process_grep_filter(const grep_target *gp, const char *sserver, const char *schannel, const char *line, char **err, BOOL *match)
{
	BOOL ok = TRUE;
	int loop = 0;

	*err = NULL;
	*match = FALSE;

	for(loop=0; loop<gp -> n_gf_list && ok; loop++)
	{
		if ((gp -> gf_list[loop].sserver == NULL || strcasecmp(gp -> gf_list[loop].sserver, sserver) == 0) &&
			(gp -> gf_list[loop].schannel == NULL || strcasecmp(gp -> gf_list[loop].schannel, schannel) == 0))
		{
			if (regexec(&gp -> gf_list[loop].filter, line, 0, NULL, 0) == 0)
			{
				*match = TRUE;

				if (gp -> gf_list[loop].file)
				{
					FILE *fh = fopen(gp -> gf_list[loop].file, "a+");
					if (!fh)
					{
						asprintf(err, "Cannot open %s: %s\n", gp -> gf_list[loop].file, strerror(errno));
						ok = FALSE;
					}
					else
					{
						if (fprintf(fh, "%s\n", line) <= 0)
						{
							asprintf(err, "Cannot write to %s: %s\n", gp -> gf_list[loop].file, strerror(errno));
							ok = FALSE;
						}

						fclose(fh);
					}
				}
			}
		}
	}

	return ok;
}
