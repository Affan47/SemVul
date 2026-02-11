snprint_hw_rr_min_io (char * buff, int len, void * data)
{
	struct hwentry * hwe = (struct hwentry *)data;

	if (!hwe->minio)
		return 0;
	if (hwe->minio == conf->minio)
		return 0;

	return snprintf(buff, len, "%u", hwe->minio);
}
