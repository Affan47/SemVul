cleanCacheDirectory (FcConfig *config, FcChar8 *dir, FcBool verbose)
{
    DIR		*d;
    struct dirent *ent;
    FcChar8	*dir_base;
    FcBool	ret = FcTrue;
    FcBool	remove;
    FcCache	*cache;
    struct stat	target_stat;

    dir_base = FcStrPlus (dir, (FcChar8 *) "/");
    if (!dir_base)
    {
	fprintf (stderr, "%s: out of memory\n", dir);
	return FcFalse;
    }
    if (access ((char *) dir, W_OK) != 0)
    {
	if (verbose)
	    printf ("%s: not cleaning %s cache directory\n", dir,
		    access ((char *) dir, F_OK) == 0 ? "unwritable" : "non-existent");
	FcStrFree (dir_base);
	return FcTrue;
    }
    if (verbose)
	printf ("%s: cleaning cache directory\n", dir);
    d = opendir ((char *) dir);
    if (!d)
    {
	perror ((char *) dir);
	FcStrFree (dir_base);
	return FcFalse;
    }
    while ((ent = readdir (d)))
    {
	FcChar8	*file_name;
	const FcChar8	*target_dir;

	if (ent->d_name[0] == '.')
	    continue;


	if (strlen(ent->d_name) != 32 + strlen ("-" FC_ARCHITECTURE FC_CACHE_SUFFIX) ||
	    strcmp(ent->d_name + 32, "-" FC_ARCHITECTURE FC_CACHE_SUFFIX))
	    continue;

	file_name = FcStrPlus (dir_base, (FcChar8 *) ent->d_name);
	if (!file_name)
	{
	    fprintf (stderr, "%s: allocation failure\n", dir);
	    ret = FcFalse;
	    break;
	}
	remove = FcFalse;
	cache = FcDirCacheLoadFile (file_name, NULL);
	if (!cache)
	{
	    if (verbose)
		printf ("%s: invalid cache file: %s\n", dir, ent->d_name);
	    remove = FcTrue;
	}
	else
	{
	    target_dir = FcCacheDir (cache);
	    if (stat ((char *) target_dir, &target_stat) < 0)
	    {
		if (verbose)
		    printf ("%s: %s: missing directory: %s \n",
			    dir, ent->d_name, target_dir);
		remove = FcTrue;
	    }
	}
	if (remove)
	{
	    if (unlink ((char *) file_name) < 0)
	    {
		perror ((char *) file_name);
		ret = FcFalse;
	    }
	}
	FcDirCacheUnload (cache);
        FcStrFree (file_name);
    }

    closedir (d);
    FcStrFree (dir_base);
    return ret;
}
