store_sampling_rate(struct dbs_data *dbs_data, const char *buf,
		size_t count)
{
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if (ret != 1)
		return -EINVAL;

	update_sampling_rate(dbs_data, input);
	return count;
}
