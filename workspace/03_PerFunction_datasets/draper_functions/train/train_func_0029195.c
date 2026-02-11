em25xx_bus_B_recv_bytes(struct em28xx *dev, u16 addr, u8 *buf,
				   u16 len)
{
	int ret;

	if (len < 1 || len > 64)
		return -EOPNOTSUPP;


	ret = dev->em28xx_read_reg_req_len(dev, 0x06, addr, buf, len);
	if (ret < 0) {
		em28xx_warn("reading from i2c device at 0x%x failed (error=%i)\n",
			    addr, ret);
		return ret;
	}


	ret = dev->em28xx_read_reg_req(dev, 0x08, 0x0000);


	if (!ret)
		return len;
	else if (ret > 0) {
		if (i2c_debug == 1)
			em28xx_warn("Bus B R08 returned 0x%02x: I2C ACK error\n",
				    ret);
		return -ENXIO;
	}

	return ret;


}
