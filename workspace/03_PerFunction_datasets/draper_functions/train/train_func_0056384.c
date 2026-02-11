img_i2c_write_fifo(struct img_i2c *i2c)
{
	while (i2c->msg.len) {
		u32 fifo_status;

		img_i2c_wr_rd_fence(i2c);
		fifo_status = img_i2c_readl(i2c, SCB_FIFO_STATUS_REG);
		if (fifo_status & FIFO_WRITE_FULL)
			break;

		img_i2c_writel(i2c, SCB_WRITE_DATA_REG, *i2c->msg.buf);
		i2c->msg.len--;
		i2c->msg.buf++;
	}


	if (!i2c->msg.len)
		i2c->int_enable &= ~INT_FIFO_EMPTYING;
}
