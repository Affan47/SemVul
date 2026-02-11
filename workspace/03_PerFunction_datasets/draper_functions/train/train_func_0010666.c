tarCreateHeader(char *h, const char *filename, const char *linktarget,
				size_t size, mode_t mode, uid_t uid, gid_t gid, time_t mtime)
{
	if (strlen(filename) > 99)
		return TAR_NAME_TOO_LONG;

	if (linktarget && strlen(linktarget) > 99)
		return TAR_SYMLINK_TOO_LONG;


	memset(h, 0, 512);


	strlcpy(&h[0], filename, 100);
	if (linktarget != NULL || S_ISDIR(mode))
	{


		int			flen = strlen(filename);

		flen = Min(flen, 99);
		h[flen] = '/';
		h[flen + 1] = '\0';
	}


	sprintf(&h[100], "%07o ", (int) (mode & 07777));


	sprintf(&h[108], "%07o ", (int) uid);


	sprintf(&h[116], "%07o ", (int) gid);


	if (linktarget != NULL || S_ISDIR(mode))

		print_val(&h[124], 0, 8, 11);
	else
		print_val(&h[124], size, 8, 11);
	sprintf(&h[135], " ");


	sprintf(&h[136], "%011o ", (int) mtime);


	if (linktarget != NULL)
	{

		sprintf(&h[156], "2");

		strlcpy(&h[157], linktarget, 100);
	}
	else if (S_ISDIR(mode))

		sprintf(&h[156], "5");
	else

		sprintf(&h[156], "0");


	sprintf(&h[257], "ustar");


	sprintf(&h[263], "00");


	strlcpy(&h[265], "postgres", 32);


	strlcpy(&h[297], "postgres", 32);


	sprintf(&h[329], "%07o ", 0);


	sprintf(&h[337], "%07o ", 0);


	sprintf(&h[148], "%06o ", tarChecksum(h));

	return TAR_OK;
}
