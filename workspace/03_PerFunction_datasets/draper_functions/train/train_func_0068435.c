check_cache_file(const char *path, int *vmajor, int *vminor)
{
	FILE *f;
	char buf[1024];
	int ret = CACHE_BAD;

	if (!(f = fopen(path, "r")))
		return CACHE_MISSING;

	if (!fgets(buf, sizeof(buf), f))
		goto done;
	if (sscanf(buf, magic, vmajor, vminor) != 2)
		goto done;
	ret = CACHE_OK;

done:
	fclose(f);
	return ret;
}
