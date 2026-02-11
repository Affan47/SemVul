zfile_getdata (struct zfile *z, uae_s64 offset, int len)
{
	uae_s64 pos = zfile_ftell (z);
	uae_u8 *b;
	if (len < 0) {
		zfile_fseek (z, 0, SEEK_END);
		len = zfile_ftell (z);
		zfile_fseek (z, 0, SEEK_SET);
	}
	b = xmalloc (uae_u8, len);
	zfile_fseek (z, offset, SEEK_SET);
	zfile_fread (b, len, 1, z);
	zfile_fseek (z, pos, SEEK_SET);
	return b;
}
