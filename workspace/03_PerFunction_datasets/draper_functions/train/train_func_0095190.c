maildirquota_countfolder(const char *folder)
{
#ifdef TRASHQUOTA

#else

	if (strcmp(folder, "." TRASH) == 0 ||
	    strcmp(folder, "." TRASH "/") == 0)
		return (0);

	for ( ; *folder; folder++)
		if (*folder == '/' &&
		    (strcmp(folder+1, "." TRASH) == 0 ||
		     strcmp(folder+1, "." TRASH "/") == 0))
			return (0);
#endif
	return (1);
}
