id3_copy_data(FILE *inf, FILE *outf, long offset, long count)
{
	const long bufsize = 65536;
	char *buf;
	size_t k;
	int ret;

	ret = 1;
	buf = malloc(bufsize);

	if (fseek(inf, offset, SEEK_SET))
		ret = M3G_ERR_READ;

	while (ret == 1 && count != 0) {
		k = (count > 0 && count < bufsize) ? count : bufsize;
		k = fread(buf, 1, k, inf);
		if (k == 0) {
			if (!feof(inf) || count > 0)
				ret = M3G_ERR_READ;
			break;
		}
		if (fwrite(buf, 1, k, outf) != k) {
			ret = M3G_ERR_WRITE;
			break;
		}
		if (count > 0)
			count -= k;
	}

	free(buf);
	return ret;
}
