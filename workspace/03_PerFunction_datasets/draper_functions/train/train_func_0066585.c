get_config(struct ddf1 *ddf1, struct ddf1_phys_drive *pd, unsigned int n)
{
	int i = get_config_index(ddf1, pd, &n);

	return i < 0 ? NULL : CR(ddf1, i);
}
