ssd_i2c_write(struct ssd_device *dev, uint8_t saddr, uint8_t size, uint8_t *buf)
{
	ssd_i2c_ctrl_t ctrl;
	ssd_i2c_data_t data;
	uint8_t off = 0;
	uint8_t status = 0;
	unsigned long st;
	int ret = 0;

	mutex_lock(&dev->i2c_mutex);

	ctrl.val = 0;


	ctrl.bits.wdata	= saddr;
	ctrl.bits.addr	= SSD_I2C_SADDR_REG;
	ctrl.bits.rw 	= SSD_I2C_CTRL_WRITE;
	__ssd_i2c_reg32_write(dev->ctrlp + SSD_I2C_CTRL_REG, ctrl.val);


	while (off < size) {
		ctrl.bits.wdata	= buf[off];
		ctrl.bits.addr	= SSD_I2C_DATA_REG;
		ctrl.bits.rw 	= SSD_I2C_CTRL_WRITE;
		__ssd_i2c_reg32_write(dev->ctrlp + SSD_I2C_CTRL_REG, ctrl.val);

		off++;
	}


	ctrl.bits.wdata	= 0x01;
	ctrl.bits.addr	= SSD_I2C_CMD_REG;
	ctrl.bits.rw 	= SSD_I2C_CTRL_WRITE;
	__ssd_i2c_reg32_write(dev->ctrlp + SSD_I2C_CTRL_REG, ctrl.val);


	st = jiffies;
	for (;;) {
		ctrl.bits.wdata	= 0;
		ctrl.bits.addr	= SSD_I2C_STATUS_REG;
		ctrl.bits.rw 	= SSD_I2C_CTRL_READ;
		__ssd_i2c_reg32_write(dev->ctrlp + SSD_I2C_CTRL_REG, ctrl.val);

		for (;;) {
			data.val = __ssd_i2c_reg32_read(dev->ctrlp + SSD_I2C_RDATA_REG);
			if (data.bits.valid == 0) {
				break;
			}


			if (time_after(jiffies, (st + SSD_I2C_TIMEOUT))) {
				ret = -ETIMEDOUT;
				goto out_clear;
			}
			cond_resched();
		}

		status = data.bits.rdata;
		if (status & 0x1) {
			break;
		}

		if (time_after(jiffies, (st + SSD_I2C_TIMEOUT))) {
			ret = -ETIMEDOUT;
			goto out_clear;
		}
		cond_resched();
	}

	if (!(status & 0x1)) {
		ret =  -1;
		goto out_clear;
	}


	if (status & 0x20) {
		ret =  -2;
		goto out_clear;
	}


	if (status & 0x10) {
		ret =  -3;
		goto out_clear;
	}


out_clear:
	if (__ssd_i2c_clear(dev, saddr)) {
		if (!ret) ret = -4;
	}

	mutex_unlock(&dev->i2c_mutex);

	return ret;
}
