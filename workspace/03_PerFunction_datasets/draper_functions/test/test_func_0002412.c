snprint_hw_product (char * buff, int len, void * data)
{
	struct hwentry * hwe = (struct hwentry *)data;

	if (!hwe->product)
		return 0;

	return snprintf(buff, len, "\"%s\"", hwe->product);
}
