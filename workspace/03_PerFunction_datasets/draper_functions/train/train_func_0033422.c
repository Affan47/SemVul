app_RAND_write_file(const char *file, BIO *bio_e)
	{
	char buffer[200];

	if (egdsocket || !seeded)


		return 0;

	if (file == NULL)
		file = RAND_file_name(buffer, sizeof buffer);
	if (file == NULL || !RAND_write_file(file))
		{
		BIO_printf(bio_e,"unable to write 'random state'\n");
		return 0;
		}
	return 1;
	}
