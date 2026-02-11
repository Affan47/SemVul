dtv5100_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msg[],
			    int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	int i;

	if (num > 2)
		return -EINVAL;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	for (i = 0; i < num; i++) {

		if (i+1 < num && (msg[i+1].flags & I2C_M_RD)) {
			if (dtv5100_i2c_msg(d, msg[i].addr, msg[i].buf,
					    msg[i].len, msg[i+1].buf,
					    msg[i+1].len) < 0)
				break;
			i++;
		} else if (dtv5100_i2c_msg(d, msg[i].addr, msg[i].buf,
					   msg[i].len, NULL, 0) < 0)
				break;
	}

	mutex_unlock(&d->i2c_mutex);
	return i;
}
