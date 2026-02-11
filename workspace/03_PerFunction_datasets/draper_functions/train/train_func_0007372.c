go7007_i2c_xfer(struct go7007 *go, u16 addr, int read,
		u16 command, int flags, u8 *data)
{
	int i, ret = -EIO;
	u16 val;

	if (go->status == STATUS_SHUTDOWN)
		return -ENODEV;

#ifdef GO7007_I2C_DEBUG
	if (read)
		dev_dbg(go->dev, "go7007-i2c: reading 0x%02x on 0x%02x\n",
			command, addr);
	else
		dev_dbg(go->dev,
			"go7007-i2c: writing 0x%02x to 0x%02x on 0x%02x\n",
			*data, command, addr);
#endif

	mutex_lock(&go->hw_lock);

	if (go->board_id == GO7007_BOARDID_ADLINK_MPG24) {

		mutex_lock(&adlink_mpg24_i2c_lock);
		go7007_write_addr(go, 0x3c82, 0x0020);
	}


	for (i = 0; i < 10; ++i) {
		if (go7007_read_addr(go, STATUS_REG_ADDR, &val) < 0)
			goto i2c_done;
		if (!(val & I2C_STATE_MASK))
			break;
		msleep(100);
	}
	if (i == 10) {
		dev_err(go->dev, "go7007-i2c: I2C adapter is hung\n");
		goto i2c_done;
	}


	go7007_write_addr(go, I2C_CTRL_REG_ADDR, flags);
	go7007_write_addr(go, I2C_LO_ADDR_REG_ADDR, command);


	if (!read) {
		go7007_write_addr(go, I2C_DATA_REG_ADDR, *data);
		go7007_write_addr(go, I2C_DEV_UP_ADDR_REG_ADDR,
					(addr << 9) | (command >> 8));
		ret = 0;
		goto i2c_done;
	}


	if (go7007_read_addr(go, I2C_DATA_REG_ADDR, &val) < 0)
		goto i2c_done;


	go7007_write_addr(go, I2C_DEV_UP_ADDR_REG_ADDR,
			(addr << 9) | 0x0100 | (command >> 8));


	for (i = 0; i < 10; ++i) {
		if (go7007_read_addr(go, STATUS_REG_ADDR, &val) < 0)
			goto i2c_done;
		if (val & I2C_READ_READY_MASK)
			break;
		msleep(100);
	}
	if (i == 10) {
		dev_err(go->dev, "go7007-i2c: I2C adapter is hung\n");
		goto i2c_done;
	}


	if (go7007_read_addr(go, I2C_DATA_REG_ADDR, &val) < 0)
		goto i2c_done;
	*data = val;
	ret = 0;

i2c_done:
	if (go->board_id == GO7007_BOARDID_ADLINK_MPG24) {

		go7007_write_addr(go, 0x3c82, 0x0000);
		mutex_unlock(&adlink_mpg24_i2c_lock);
	}
	mutex_unlock(&go->hw_lock);
	return ret;
}
