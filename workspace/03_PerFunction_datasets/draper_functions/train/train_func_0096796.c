swan_find_upgrade_file(const char *tmp_file)
{
	unsigned int i;
	int ret;
	const char *dev_list[] = {SDCARD_DEVICE "p1", SDCARD_DEVICE, EMMC_DEVICE "p1", EMMC_DEVICE};

	system_command("rm /tmp/* %s -rf", tmp_file);

	for (i = 0; i < ARRAY_SIZE(dev_list); i++)
	{
		ret = swan_find_upgrade_file_from(dev_list[i], tmp_file);
		if (ret >= 0)
		{
			return 0;
		}
	}

	return -1;
}
