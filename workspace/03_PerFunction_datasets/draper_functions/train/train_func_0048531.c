get_key_flydvb_trio(struct IR_i2c *ir, enum rc_type *protocol,
			       u32 *scancode, u8 *toggle)
{
	int gpio;
	int attempt = 0;
	unsigned char b;


	struct saa7134_dev *dev = ir->c->adapter->algo_data;

	if (dev == NULL) {
		ir_dbg(ir, "get_key_flydvb_trio: "
			   "ir->c->adapter->algo_data is NULL!\n");
		return -EIO;
	}


	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);

	gpio = saa_readl(SAA7134_GPIO_GPSTATUS0 >> 2);

	if (0x40000 & ~gpio)
		return 0;


	b = 0;

	while (1 != i2c_master_send(ir->c, &b, 1)) {
		if ((attempt++) < 10) {


			msleep(10);
			continue;
		}
		ir_dbg(ir, "send wake up byte to pic16C505 (IR chip)"
			   "failed %dx\n", attempt);
		return -EIO;
	}
	if (1 != i2c_master_recv(ir->c, &b, 1)) {
		ir_dbg(ir, "read error\n");
		return -EIO;
	}

	*protocol = RC_TYPE_UNKNOWN;
	*scancode = b;
	*toggle = 0;
	return 1;
}
