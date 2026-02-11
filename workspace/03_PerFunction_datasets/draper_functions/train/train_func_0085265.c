set_brightness_shadow(int brightness, int step, u32 msec)
{
	int fd;
	char buff[32];
	int ret;
	ssize_t readlen;
	int current_brightness;

	fd = open(BRIGHTNESS_PATH, O_RDWR | O_SYNC | O_BINARY);
	if (fd < 0)
	{
		print_error("open file \"" BRIGHTNESS_PATH "\" failed");
		return fd;
	}

	readlen = read(fd, buff, sizeof(buff));
	if (readlen < 0)
	{
		ret = readlen;
		print_error("read");
		goto out_close_fd;
	}

	buff[readlen] = 0;

	current_brightness = text2value_unsigned(buff, NULL, 10);

	if (current_brightness > brightness)
	{
		ret = fset_brightness_shadow_decrease(fd, current_brightness, brightness, step, msec);
	}
	else if (current_brightness < brightness)
	{
		ret = fset_brightness_shadow_increase(fd, current_brightness, brightness, step, msec);
	}
	else
	{
		ret = 0;
	}

out_close_fd:
	close(fd);

	return ret;
}
