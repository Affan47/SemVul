slot_reset(struct dvb_ca_en50221 *ca, int slot)
{
	struct cxd *ci = ca->data;

	mutex_lock(&ci->lock);
#if 0
	write_reg(ci, 0x00, 0x21);
	write_reg(ci, 0x06, 0x1F);
	write_reg(ci, 0x00, 0x31);
#else
#if 0
	write_reg(ci, 0x06, 0x1F);
	write_reg(ci, 0x06, 0x2F);
#else
	cam_mode(ci, 0);
	write_reg(ci, 0x00, 0x21);
	write_reg(ci, 0x06, 0x1F);
	write_reg(ci, 0x00, 0x31);
	write_regm(ci, 0x20, 0x80, 0x80);
	write_reg(ci, 0x03, 0x02);
	ci->ready = 0;
#endif
#endif
	ci->mode = -1;
	{
		int i;
#if 0
		u8 val;
#endif
		for (i = 0; i < 100; i++) {
			usleep_range(10000, 11000);
#if 0
			read_reg(ci, 0x06, &val);
			dev_info(&ci->i2c->dev, "%d:%02x\n", i, val);
			if (!(val&0x10))
				break;
#else
			if (ci->ready)
				break;
#endif
		}
	}
	mutex_unlock(&ci->lock);

	return 0;
}
