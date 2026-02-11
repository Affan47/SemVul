FcConfigParseAndLoadDir (FcConfig	*config,
			 const FcChar8	*name,
			 const FcChar8	*dir,
			 FcBool		complain)
{
    DIR		    *d;
    struct dirent   *e;
    FcBool	    ret = FcTrue;
    FcChar8	    *file;
    FcChar8	    *base;
    FcStrSet	    *files;

    d = opendir ((char *) dir);
    if (!d)
    {
	if (complain)
	    FcConfigMessage (0, FcSevereError, "Cannot open config dir \"%s\"",
			     name);
	ret = FcFalse;
	goto bail0;
    }

    file = (FcChar8 *) malloc (strlen ((char *) dir) + 1 + FC_MAX_FILE_LEN + 1);
    if (!file)
    {
	ret = FcFalse;
	goto bail1;
    }

    strcpy ((char *) file, (char *) dir);
    strcat ((char *) file, "/");
    base = file + strlen ((char *) file);

    files = FcStrSetCreate ();
    if (!files)
    {
	ret = FcFalse;
	goto bail2;
    }

    if (FcDebug () & FC_DBG_CONFIG)
	printf ("\tScanning config dir %s\n", dir);

    while (ret && (e = readdir (d)))
    {
	int d_len;
#define TAIL	    ".conf"
#define TAIL_LEN    5


	if ('0' <= e->d_name[0] && e->d_name[0] <= '9' &&
	    (d_len = strlen (e->d_name)) < FC_MAX_FILE_LEN &&
	    d_len > TAIL_LEN &&
	    strcmp (e->d_name + d_len - TAIL_LEN, TAIL) == 0)
	{
	    strcpy ((char *) base, (char *) e->d_name);
	    if (!FcStrSetAdd (files, file))
	    {
		ret = FcFalse;
		goto bail3;
	    }
	}
    }
    if (ret)
    {
	int i;
	qsort (files->strs, files->num, sizeof (FcChar8 *),
	       (int (*)(const void *, const void *)) FcSortCmpStr);
	for (i = 0; ret && i < files->num; i++)
	    ret = FcConfigParseAndLoad (config, files->strs[i], complain);
    }
bail3:
    FcStrSetDestroy (files);
bail2:
    free (file);
bail1:
    closedir (d);
bail0:
    return ret || !complain;
}
