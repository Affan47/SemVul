cm_store_files_ca_read(void *parent, const char *filename)
{
	FILE *fp;
	struct cm_store_ca *ret;
	if (filename != NULL) {
		fp = fopen(filename, "r");
		if (fp != NULL) {
			ret = cm_store_ca_read(parent, filename, fp);
			fclose(fp);
		} else {
			ret = NULL;
		}
	} else {
		ret = NULL;
	}
	return ret;
}
