usbvision_i2c_read_max4(struct usb_usbvision *usbvision, unsigned char addr,
		     char *buf, short len)
{
	int rc, retries;

	for (retries = 5;;) {
		rc = usbvision_write_reg(usbvision, USBVISION_SER_ADRS, addr);
		if (rc < 0)
			return rc;


		rc = usbvision_write_reg(usbvision, USBVISION_SER_CONT,
				      (len & 0x07) | 0x18);
		if (rc < 0)
			return rc;


		do {

			rc = usbvision_read_reg(usbvision, USBVISION_SER_CONT);
		} while (rc > 0 && ((rc & 0x10) != 0));
		if (rc < 0)
			return rc;


		if ((rc & 0x20) == 0)
			break;


		rc = usbvision_write_reg(usbvision, USBVISION_SER_CONT, 0x00);
		if (rc < 0)
			return rc;

		if (--retries < 0)
			return -1;
	}

	switch (len) {
	case 4:
		buf[3] = usbvision_read_reg(usbvision, USBVISION_SER_DAT4);
	case 3:
		buf[2] = usbvision_read_reg(usbvision, USBVISION_SER_DAT3);
	case 2:
		buf[1] = usbvision_read_reg(usbvision, USBVISION_SER_DAT2);
	case 1:
		buf[0] = usbvision_read_reg(usbvision, USBVISION_SER_DAT1);
		break;
	default:
		printk(KERN_ERR
		       "usbvision_i2c_read_max4: buffer length > 4\n");
	}

	if (i2c_debug & DBG_I2C) {
		int idx;

		for (idx = 0; idx < len; idx++)
			PDEBUG(DBG_I2C, "read %x from address %x", (unsigned char)buf[idx], addr);
	}
	return len;
}
