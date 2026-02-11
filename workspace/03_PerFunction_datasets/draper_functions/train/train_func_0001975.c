eeprom_read(struct file *filp, struct kobject *kobj,
			   struct bin_attribute *bin_attr, char *buf,
			   loff_t off, size_t count)
{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	int todo = count;

	count = w1_f2d_fix_count(off, count, W1_F2D_EEPROM_SIZE);
	if (count == 0)
		return 0;

	mutex_lock(&sl->master->bus_mutex);


	while (todo > 0) {
		int block_read;

		if (todo >= W1_F2D_READ_MAXLEN)
			block_read = W1_F2D_READ_MAXLEN;
		else
			block_read = todo;

		if (w1_f2d_readblock(sl, off, block_read, buf) < 0)
			count = -EIO;

		todo -= W1_F2D_READ_MAXLEN;
		buf += W1_F2D_READ_MAXLEN;
		off += W1_F2D_READ_MAXLEN;
	}

	mutex_unlock(&sl->master->bus_mutex);

	return count;
}
