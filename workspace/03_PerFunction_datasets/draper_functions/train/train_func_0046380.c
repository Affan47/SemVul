rename(char *oldfile, char *newfile)
{
    int status;
    status = ::rename(oldfile, newfile);

    if (params.use_metafiles)
    {
	char old_metafile[PATH_MAX];
	char new_metafile[PATH_MAX];

	meta_filename(oldfile, old_metafile);
	meta_filename(newfile, new_metafile);

	if (verbose>1) DAPLOG((LOG_INFO, "renaming metafile %s to %s\n",
			       old_metafile, new_metafile));
	::rename(old_metafile, new_metafile);
    }
    return status;
}
