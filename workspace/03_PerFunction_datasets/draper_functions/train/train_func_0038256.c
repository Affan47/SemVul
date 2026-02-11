ds1511_nvram_read(struct file *filp, struct kobject *kobj,
		  struct bin_attribute *ba,
		  char *buf, loff_t pos, size_t size)
{
	ssize_t count;

	rtc_write(pos, DS1511_RAMADDR_LSB);
	for (count = 0; count < size; count++)
		*buf++ = rtc_read(DS1511_RAMDATA);

	return count;
}
