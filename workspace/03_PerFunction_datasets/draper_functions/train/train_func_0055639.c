ReadDataFromArchiveZlib(ArchiveHandle *AH, ReadFunc readF)
{
	z_streamp	zp;
	char	   *out;
	int			res = Z_OK;
	size_t		cnt;
	char	   *buf;
	size_t		buflen;

	zp = (z_streamp) pg_malloc(sizeof(z_stream));
	zp->zalloc = Z_NULL;
	zp->zfree = Z_NULL;
	zp->opaque = Z_NULL;

	buf = pg_malloc(ZLIB_IN_SIZE);
	buflen = ZLIB_IN_SIZE;

	out = pg_malloc(ZLIB_OUT_SIZE + 1);

	if (inflateInit(zp) != Z_OK)
		exit_horribly(modulename,
					  "could not initialize compression library: %s\n",
					  zp->msg);


	while ((cnt = readF(AH, &buf, &buflen)))
	{

		checkAborting(AH);

		zp->next_in = (void *) buf;
		zp->avail_in = cnt;

		while (zp->avail_in > 0)
		{
			zp->next_out = (void *) out;
			zp->avail_out = ZLIB_OUT_SIZE;

			res = inflate(zp, 0);
			if (res != Z_OK && res != Z_STREAM_END)
				exit_horribly(modulename,
							  "could not uncompress data: %s\n", zp->msg);

			out[ZLIB_OUT_SIZE - zp->avail_out] = '\0';
			ahwrite(out, 1, ZLIB_OUT_SIZE - zp->avail_out, AH);
		}
	}

	zp->next_in = NULL;
	zp->avail_in = 0;
	while (res != Z_STREAM_END)
	{
		zp->next_out = (void *) out;
		zp->avail_out = ZLIB_OUT_SIZE;
		res = inflate(zp, 0);
		if (res != Z_OK && res != Z_STREAM_END)
			exit_horribly(modulename,
						  "could not uncompress data: %s\n", zp->msg);

		out[ZLIB_OUT_SIZE - zp->avail_out] = '\0';
		ahwrite(out, 1, ZLIB_OUT_SIZE - zp->avail_out, AH);
	}

	if (inflateEnd(zp) != Z_OK)
		exit_horribly(modulename,
					  "could not close compression library: %s\n", zp->msg);

	free(buf);
	free(out);
	free(zp);
}
