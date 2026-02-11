proc_set_read_reg(struct file *file, const char __user *buffer,
		unsigned long count, void *data)
{
	char tmp[16];
	u32 addr, len;

	if (count < 2) {
		DBG_88E("argument size is less than 2\n");
		return -EFAULT;
	}

	if (buffer && !copy_from_user(tmp, buffer, sizeof(tmp))) {
		int num = sscanf(tmp, "%x %x", &addr, &len);

		if (num !=  2) {
			DBG_88E("invalid read_reg parameter!\n");
			return count;
		}

		proc_get_read_addr = addr;

		proc_get_read_len = len;
	}

	return count;
}
