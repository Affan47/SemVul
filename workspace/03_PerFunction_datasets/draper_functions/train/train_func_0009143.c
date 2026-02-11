eeprom_write(struct file *filp, struct kobject *kobj,
			    struct bin_attribute *bin_attr, char *buf,
			    loff_t off, size_t count)

{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	int addr, len, idx;

	count = w1_f1C_fix_count(off, count, W1_EEPROM_SIZE);
	if (count == 0)
		return 0;

	if (w1_enable_crccheck) {

		if ((off & W1_PAGE_MASK) || (count & W1_PAGE_MASK)) {
			dev_err(&sl->dev, "invalid offset/count off=%d cnt=%zd\n",
				(int)off, count);
			return -EINVAL;
		}


		for (idx = 0; idx < count; idx += W1_PAGE_SIZE) {
			if (crc16(CRC16_INIT, &buf[idx], W1_PAGE_SIZE)
				!= CRC16_VALID) {
				dev_err(&sl->dev, "bad CRC at offset %d\n",
					(int)off);
				return -EINVAL;
			}
		}
	}

	mutex_lock(&sl->master->mutex);


	idx = 0;
	while (idx < count) {
		addr = off + idx;
		len = W1_PAGE_SIZE - (addr & W1_PAGE_MASK);
		if (len > (count - idx))
			len = count - idx;

		if (w1_f1C_write(sl, addr, len, &buf[idx]) < 0) {
			count = -EIO;
			goto out_up;
		}
		idx += len;
	}

out_up:
	mutex_unlock(&sl->master->mutex);

	return count;
}
