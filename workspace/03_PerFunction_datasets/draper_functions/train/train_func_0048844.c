o2hb_heartbeat_group_mode_store(struct config_item *item,
		const char *page, size_t count)
{
	unsigned int i;
	int ret;
	size_t len;

	len = (page[count - 1] == '\n') ? count - 1 : count;
	if (!len)
		return -EINVAL;

	for (i = 0; i < O2HB_HEARTBEAT_NUM_MODES; ++i) {
		if (strncasecmp(page, o2hb_heartbeat_mode_desc[i], len))
			continue;

		ret = o2hb_global_heartbeat_mode_set(i);
		if (!ret)
			printk(KERN_NOTICE "o2hb: Heartbeat mode set to %s\n",
			       o2hb_heartbeat_mode_desc[i]);
		return count;
	}

	return -EINVAL;

}
