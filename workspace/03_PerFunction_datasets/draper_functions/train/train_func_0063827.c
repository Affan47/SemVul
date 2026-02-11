snprint_hw_flush_on_last_del (char * buff, int len, void * data)
{
	struct hwentry * hwe = (struct hwentry *)data;

	switch (hwe->flush_on_last_del) {
	case FLUSH_DISABLED:
		return snprintf(buff, len, "no");
	case FLUSH_ENABLED:
		return snprintf(buff, len, "yes");
	}
	return 0;
}
