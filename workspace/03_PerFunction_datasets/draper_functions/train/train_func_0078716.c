addrbook_write_elem_s(FILE *fp, gint lvl, gchar *name)
{
	gint i;
	for (i = 0; i < lvl; i++)
		if (fputs("  ", fp) == EOF)
			return -1;
	if (fputs("<", fp) == EOF)
		return -1;
	if (fputs(name, fp) == EOF)
		return -1;

	return 0;
}
