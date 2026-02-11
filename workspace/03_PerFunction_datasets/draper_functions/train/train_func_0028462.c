make_sd_card(const char *dev_name)
{
	int ret;

	ret = system_command("sudo umount %s*", dev_name);
	if (ret < 0)
	{
		print_error("system_command");
		return ret;
	}

	ret = system_command("sudo sfdisk -uM %s << EOF\n100,,L\nEOF\n", dev_name);
	if (ret < 0)
	{
		print_error("system_command");
		return ret;
	}

	ret = system_command("sudo mkfs.vfat %s1", dev_name);
	if (ret < 0)
	{
		print_error("system_command");
	}

	return ret;
}
