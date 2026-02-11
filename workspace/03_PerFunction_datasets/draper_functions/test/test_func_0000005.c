opera1_usb_i2c_msgxfer(struct dvb_usb_device *dev, u16 addr,
				  u8 * buf, u16 len)
{
	int ret = 0;
	u8 request;
	u16 value;

	if (!dev) {
		info("no usb_device");
		return -EINVAL;
	}
	if (mutex_lock_interruptible(&dev->usb_mutex) < 0)
		return -EAGAIN;

	switch (addr>>1){
		case ADDR_B600_VOLTAGE_13V:
			request=0xb6;
			value=0x00;
			break;
		case ADDR_B601_VOLTAGE_18V:
			request=0xb6;
			value=0x01;
			break;
		case ADDR_B1A6_STREAM_CTRL:
			request=0xb1;
			value=0xa6;
			break;
		case ADDR_B880_READ_REMOTE:
			request=0xb8;
			value=0x80;
			break;
		default:
			request=0xb1;
			value=addr;
	}
	ret = opera1_xilinx_rw(dev->udev, request,
		value, buf, len,
		addr&0x01?OPERA_READ_MSG:OPERA_WRITE_MSG);

	mutex_unlock(&dev->usb_mutex);
	return ret;
}
