SlruScanDirectory(SlruCtl ctl, int cutoffPage, bool doDeletions)
{
	bool		found = false;
	DIR		   *cldir;
	struct dirent *clde;
	int			segno;
	int			segpage;
	char		path[MAXPGPATH];


	cutoffPage -= cutoffPage % SLRU_PAGES_PER_SEGMENT;

	cldir = AllocateDir(ctl->Dir);
	while ((clde = ReadDir(cldir, ctl->Dir)) != NULL)
	{
		if (strlen(clde->d_name) == 4 &&
			strspn(clde->d_name, "0123456789ABCDEF") == 4)
		{
			segno = (int) strtol(clde->d_name, NULL, 16);
			segpage = segno * SLRU_PAGES_PER_SEGMENT;
			if (ctl->PagePrecedes(segpage, cutoffPage))
			{
				found = true;
				if (doDeletions)
				{
					snprintf(path, MAXPGPATH, "%s/%s", ctl->Dir, clde->d_name);
					ereport(DEBUG2,
							(errmsg("removing file \"%s\"", path)));
					unlink(path);
				}
			}
		}
	}
	FreeDir(cldir);

	return found;
}
