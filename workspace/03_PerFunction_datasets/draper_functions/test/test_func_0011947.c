ft5406_firmware_upgrade_fd(int dev_fd, const char *cfgpath)
{
	int ret;
	char buff[KB(50)] ;
	ssize_t writelen, bufflen;
	u8 checksum[2];

	bufflen = ft5406_read_firmware_data3(cfgpath, buff, sizeof(buff)) - 2;
	if (bufflen < 6)
	{
		pr_red_info("ft5406_parse_app_file");
		return bufflen;
	}

	println("bufflen = %" PRINT_FORMAT_SIZE, bufflen);

	ret = ft5406_upgrade_enter(dev_fd);
	if (ret < 0)
	{
		pr_red_info("ft5406_upgrade_start");
		return ret;
	}

	ret = ft5406_erase_app(dev_fd);
	if (ret < 0)
	{
		pr_red_info("ft5406_erase_app");
		return ret;
	}

	writelen = write(dev_fd, buff, bufflen - 6);
	if (writelen < 0)
	{
		pr_red_info("write");
		return writelen;
	}

	writelen = ft5406_firmware_write_last_data(dev_fd, buff + writelen, 6);
	if (writelen < 0)
	{
		pr_red_info("ft5406_firmware_write_last_data");
		return writelen;
	}

	ret = ft5406_read_checksum(dev_fd, checksum);
	if (ret < 0)
	{
		pr_red_info("ft5406_read_checksum");
		return ret;
	}

	checksum[1] = ft5406_calculate_checksum(buff, bufflen);

	pr_bold_info("Source checksum = 0x%02x, Dest checksum = 0x%02x", checksum[1], checksum[0]);

	if (checksum[0] != checksum[1])
	{
		pr_red_info("Checksum do't match");
		return -EFAULT;
	}

	return ft5406_upgrade_finish(dev_fd);
}
