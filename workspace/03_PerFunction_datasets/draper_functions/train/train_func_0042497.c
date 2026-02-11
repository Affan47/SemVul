fset_brightness_shadow_decrease(int fd, int current, int target, int step, u32 msec)
{
	char buff[32];
	int writelen;

	while (current - step > target)
	{
		current -= step;

		writelen = value2text_base(current, buff, 0, 0, 10) - buff;
		writelen = write(fd, buff, writelen);
		if (writelen < 0)
		{
			return writelen;
		}

		msleep(msec);
	}

	writelen = value2text_base(target, buff, 0, 0, 10) - buff;

	return write(fd, buff, writelen);
}
