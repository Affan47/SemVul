check_file(const char *fn)
{
	char	chkfn[SMALLBUF];
	FILE	*f;

	snprintf(chkfn, sizeof(chkfn), "%s/%s", confpath(), fn);

	f = fopen(chkfn, "r");

	if (!f) {
		upslog_with_errno(LOG_ERR, "Reload failed: can't open %s", chkfn);
		return 0;
	}

	fclose(f);
	return 1;
}
