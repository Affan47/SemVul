file_nokraw_save(FILE *file, gn_ringtone *ringtone, int dct4)
{
	int n;
	char buf[4096];
	gn_error err;

	n = sizeof(buf);
	if ((err = pnok_ringtone_to_raw(buf, &n, ringtone, dct4)) != GN_ERR_NONE) return err;

	if (fwrite(buf, n, 1, file) != 1) return GN_ERR_UNKNOWN;

	return GN_ERR_NONE;
}
