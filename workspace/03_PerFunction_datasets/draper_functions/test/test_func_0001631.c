sdebug_device_create(struct sdebug_host_info *sdbg_host, gfp_t flags)
{
	struct sdebug_dev_info *devip;

	devip = kzalloc(sizeof(*devip), flags);
	if (devip) {
		devip->sdbg_host = sdbg_host;
		list_add_tail(&devip->dev_list, &sdbg_host->dev_info_list);
	}
	return devip;
}
