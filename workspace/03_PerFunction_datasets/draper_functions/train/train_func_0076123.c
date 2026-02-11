GMT_putdefaults (char *this_file)
{
	if (this_file)
		GMT_savedefaults (this_file);
	else if (GMT_TMPDIR) {
		char *path = CNULL;
		path = (char *) GMT_memory (VNULL, (GMT_LONG)(strlen (GMT_TMPDIR) + 15), sizeof (char), "GMT");
		sprintf (path, "%s/.gmtdefaults4", GMT_TMPDIR);
		GMT_savedefaults (path);
		GMT_free(path);
	}
	else
		GMT_savedefaults (".gmtdefaults4");
}
