download_file(char *file, char *outfile)
{
	int i;

#ifdef DEBUG
	printf("==> download_file(file=\"%s\", outfile=\"%s\")\n",
	       file, outfile);
#endif

	i = dl_get_type(file);

	if (download_types[i].ut_download == NULL)
	{
		fprintf(stderr,
			"  ! download_file(): %.*s URLs are not supported\n",
			strcspn(download_types[i].ut_type, ":"),
			download_types[i].ut_type);
		errno = EINVAL;
		return -1;
	}

	return (*(download_types[i].ut_download))(file, outfile);
}
