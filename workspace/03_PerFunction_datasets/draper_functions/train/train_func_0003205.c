force_pr_aptpl_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_dev_attrib *da = to_attrib(item);
	bool flag;
	int ret;

	ret = strtobool(page, &flag);
	if (ret < 0)
		return ret;
	if (da->da_dev->export_count) {
		pr_err("dev[%p]: Unable to set force_pr_aptpl while"
		       " export_count is %d\n",
		       da->da_dev, da->da_dev->export_count);
		return -EINVAL;
	}

	da->force_pr_aptpl = flag;
	pr_debug("dev[%p]: SE Device force_pr_aptpl: %d\n", da->da_dev, flag);
	return count;
}
