_tarAddFile(ArchiveHandle *AH, TAR_MEMBER *th)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	FILE	   *tmp = th->tmpFH;
	char		buf[32768];
	size_t		cnt;
	pgoff_t		len = 0;
	size_t		res;
	size_t		i,
				pad;


	fseeko(tmp, 0, SEEK_END);
	th->fileLen = ftello(tmp);
	fseeko(tmp, 0, SEEK_SET);


	if (th->fileLen > MAX_TAR_MEMBER_FILELEN)
		die_horribly(AH, modulename, "archive member too large for tar format\n");

	_tarWriteHeader(th);

	while ((cnt = fread(buf, 1, sizeof(buf), tmp)) > 0)
	{
		res = fwrite(buf, 1, cnt, th->tarFH);
		if (res != cnt)
			die_horribly(AH, modulename,
						 "could not write to output file: %s\n",
						 strerror(errno));
		len += res;
	}

	if (fclose(tmp) != 0)
		die_horribly(AH, modulename, "could not close temporary file: %s\n",
					 strerror(errno));

	if (len != th->fileLen)
	{
		char		buf1[32],
					buf2[32];

		snprintf(buf1, sizeof(buf1), INT64_FORMAT, (int64) len);
		snprintf(buf2, sizeof(buf2), INT64_FORMAT, (int64) th->fileLen);
		die_horribly(AH, modulename, "actual file length (%s) does not match expected (%s)\n",
					 buf1, buf2);
	}

	pad = ((len + 511) & ~511) - len;
	for (i = 0; i < pad; i++)
	{
		if (fputc('\0', th->tarFH) == EOF)
			die_horribly(AH, modulename, "could not output padding at end of tar member\n");
	}

	ctx->tarFHpos += len + pad;
}
