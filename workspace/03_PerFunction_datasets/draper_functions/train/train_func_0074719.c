viafb_dvp1_proc_write(struct file *file,
	const char __user *buffer, size_t count, loff_t *pos)
{
	char buf[20], *value, *pbuf;
	u8 reg_val = 0;
	unsigned long length, i;
	if (count < 1)
		return -EINVAL;
	length = count > 20 ? 20 : count;
	if (copy_from_user(&buf[0], buffer, length))
		return -EFAULT;
	buf[length - 1] = '\0';
	pbuf = &buf[0];
	for (i = 0; i < 3; i++) {
		value = strsep(&pbuf, " ");
		if (value != NULL) {
			if (kstrtou8(value, 0, &reg_val) < 0)
				return -EINVAL;
			switch (i) {
			case 0:
				viafb_write_reg_mask(CR9B, VIACR,
					reg_val, 0x0f);
				break;
			case 1:
				viafb_write_reg_mask(SR65, VIASR,
					reg_val << 2, 0x0c);
				break;
			case 2:
				viafb_write_reg_mask(SR65, VIASR,
					reg_val, 0x03);
				break;
			default:
				break;
			}
		} else {
			break;
		}
	}
	return count;
}
