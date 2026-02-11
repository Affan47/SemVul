devres_release(struct device *dev, dr_release_t release,
		   dr_match_t match, void *match_data)
{
	void *res;

	res = devres_remove(dev, release, match, match_data);
	if (unlikely(!res))
		return -ENOENT;

	(*release)(dev, res);
	devres_free(res);
	return 0;
}
