dev_name_store(struct config_item *item, const char *buf,
		size_t count)
{
	struct netconsole_target *nt = to_target(item);
	size_t len;

	mutex_lock(&dynamic_netconsole_mutex);
	if (nt->enabled) {
		pr_err("target (%s) is enabled, disable to update parameters\n",
		       config_item_name(&nt->item));
		mutex_unlock(&dynamic_netconsole_mutex);
		return -EINVAL;
	}

	strlcpy(nt->np.dev_name, buf, IFNAMSIZ);


	len = strnlen(nt->np.dev_name, IFNAMSIZ);
	if (nt->np.dev_name[len - 1] == '\n')
		nt->np.dev_name[len - 1] = '\0';

	mutex_unlock(&dynamic_netconsole_mutex);
	return strnlen(buf, count);
}
