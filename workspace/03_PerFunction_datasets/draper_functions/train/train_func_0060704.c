tda8290_probe(struct tuner_i2c_props *i2c_props)
{
#define TDA8290_ID 0x89
	u8 reg = 0x1f, id;
	struct i2c_msg msg_read[] = {
		{ .addr = i2c_props->addr, .flags = 0, .len = 1, .buf = &reg },
		{ .addr = i2c_props->addr, .flags = I2C_M_RD, .len = 1, .buf = &id },
	};


	if (i2c_transfer(i2c_props->adap, msg_read, 2) != 2) {
		printk(KERN_WARNING "%s: couldn't read register 0x%02x\n",
			       __func__, reg);
		return -ENODEV;
	}

	if (id == TDA8290_ID) {
		if (debug)
			printk(KERN_DEBUG "%s: tda8290 detected @ %d-%04x\n",
			       __func__, i2c_adapter_id(i2c_props->adap),
			       i2c_props->addr);
		return 0;
	}
	return -ENODEV;
}
