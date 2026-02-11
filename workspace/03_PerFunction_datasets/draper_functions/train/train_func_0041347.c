at24_read(struct at24_data *at24,
		char *buf, loff_t off, size_t count)
{
	ssize_t retval = 0;

	if (unlikely(!count))
		return count;

	if (off + count > at24->chip.byte_len)
		return -EINVAL;


	mutex_lock(&at24->lock);

	while (count) {
		ssize_t	status;

		status = at24_eeprom_read(at24, buf, off, count);
		if (status <= 0) {
			if (retval == 0)
				retval = status;
			break;
		}
		buf += status;
		off += status;
		count -= status;
		retval += status;
	}

	mutex_unlock(&at24->lock);

	return retval;
}
