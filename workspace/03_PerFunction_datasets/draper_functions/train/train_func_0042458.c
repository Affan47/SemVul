FcDirChecksum (const FcChar8 *dir, time_t *checksum)
{
    struct Adler32 ctx;
    struct dirent **files;
    int n, ret = 0;
#ifndef HAVE_STRUCT_DIRENT_D_TYPE
    size_t len = strlen ((const char *)dir);
#endif

    Adler32Init (&ctx);

    n = scandir ((const char *)dir, &files,
#ifdef HAVE_STRUCT_DIRENT_D_TYPE
		 &FcDirChecksumScandirFilter,
#else
		 NULL,
#endif
		 &FcDirChecksumScandirSorter);
    if (n == -1)
	return -1;

    while (n--)
    {
	size_t dlen = strlen (files[n]->d_name);
	int dtype;

#ifdef HAVE_STRUCT_DIRENT_D_TYPE
	dtype = files[n]->d_type;
#else
	struct stat statb;
	char f[PATH_MAX + 1];

	memcpy (f, dir, len);
	f[len] = FC_DIR_SEPARATOR;
	memcpy (&f[len + 1], files[n]->d_name, dlen);
	f[len + 1 + dlen] = 0;
	if (lstat (f, &statb) < 0)
	{
	    ret = -1;
	    goto bail;
	}
	if (S_ISDIR (statb.st_mode))
	    goto bail;

	dtype = statb.st_mode;
#endif
	Adler32Update (&ctx, files[n]->d_name, dlen + 1);
	Adler32Update (&ctx, (char *)&dtype, sizeof (int));

#ifndef HAVE_STRUCT_DIRENT_D_TYPE
      bail:
#endif
	free (files[n]);
    }
    free (files);
    if (ret == -1)
	return -1;

    *checksum = Adler32Finish (&ctx);

    return 0;
}
