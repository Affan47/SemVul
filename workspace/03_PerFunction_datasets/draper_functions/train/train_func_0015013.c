proc_set_write_reg(struct file *file, const char __user *buffer,
		unsigned long count, void *data)
{
	struct net_device *dev = data;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev);
	char tmp[32];
	u32 addr, val, len;

	if (count < 3) {
		DBG_88E("argument size is less than 3\n");
		return -EFAULT;
	}

	if (buffer && !copy_from_user(tmp, buffer, sizeof(tmp))) {
		int num = sscanf(tmp, "%x %x %x", &addr, &val, &len);

		if (num !=  3) {
			DBG_88E("invalid write_reg parameter!\n");
			return count;
		}
		switch (len) {
		case 1:
			usb_write8(padapter, addr, (u8)val);
			break;
		case 2:
			usb_write16(padapter, addr, (u16)val);
			break;
		case 4:
			usb_write32(padapter, addr, val);
			break;
		default:
			DBG_88E("error write length =%d", len);
			break;
		}
	}
	return count;
}
