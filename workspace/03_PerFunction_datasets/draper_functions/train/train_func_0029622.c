saa7134_i2c_eeprom_md7134_gate(struct saa7134_dev *dev)
{
	u8 subaddr = 0x7, dmdregval;
	u8 data[2];
	int ret;
	struct i2c_msg i2cgatemsg_r[] = { {.addr = 0x08, .flags = 0,
					   .buf = &subaddr, .len = 1},
					  {.addr = 0x08,
					   .flags = I2C_M_RD,
					   .buf = &dmdregval, .len = 1}
					};
	struct i2c_msg i2cgatemsg_w[] = { {.addr = 0x08, .flags = 0,
					   .buf = data, .len = 2} };

	ret = i2c_transfer(&dev->i2c_adap, i2cgatemsg_r, 2);
	if ((ret == 2) && (dmdregval & 0x2)) {
		pr_debug("%s: DVB-T demod i2c gate was left closed\n",
			 dev->name);

		data[0] = subaddr;
		data[1] = (dmdregval & ~0x2);
		if (i2c_transfer(&dev->i2c_adap, i2cgatemsg_w, 1) != 1)
			pr_err("%s: EEPROM i2c gate open failure\n",
			  dev->name);
	}
}
