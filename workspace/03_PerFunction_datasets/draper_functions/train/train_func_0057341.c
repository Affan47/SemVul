unix_name(doscp_t *dosCp,
		   const char *base, const char *ext, char Case, wchar_t *ret)
{
	char *s, tname[9], text[4], ans[13];
	int i;

	strncpy(tname, base, 8);
	tname[8] = '\0';
	if ((s = strchr(tname, ' ')))
		*s = '\0';

	if(!(Case & (BASECASE | EXTCASE)) && mtools_ignore_short_case)
		Case |= BASECASE | EXTCASE;

	if(Case & BASECASE)
		for(i=0;i<8 && tname[i];i++)
			tname[i] = tolower(tname[i]);

	strncpy(text, ext, 3);
	text[3] = '\0';
	if ((s = strchr(text, ' ')))
		*s = '\0';

	if(Case & EXTCASE)
		for(i=0;i<3 && text[i];i++)
			text[i] = tolower(text[i]);

	if (*text) {
		strcpy(ans, tname);
		strcat(ans, ".");
		strcat(ans, text);
	} else
		strcpy(ans, tname);


	dos_to_wchar(dosCp, ans, ret, 12);
	return ret;
}
