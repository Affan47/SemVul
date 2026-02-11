dump_sb(const char* spec)
{
	struct exfat_dev* dev;
	struct exfat_super_block sb;

	dev = exfat_open(spec, EXFAT_MODE_RO);
	if (dev == NULL)
		return 1;

	if (exfat_read(dev, &sb, sizeof(struct exfat_super_block)) < 0)
	{
		exfat_close(dev);
		exfat_error("failed to read from `%s'", spec);
		return 1;
	}
	if (memcmp(sb.oem_name, "EXFAT   ", sizeof(sb.oem_name)) != 0)
	{
		exfat_close(dev);
		exfat_error("exFAT file system is not found on `%s'", spec);
		return 1;
	}

	print_generic_info(&sb);
	print_sector_info(&sb);
	print_cluster_info(&sb);
	print_other_info(&sb);

	exfat_close(dev);
	return 0;
}
