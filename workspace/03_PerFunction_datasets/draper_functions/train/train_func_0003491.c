xlp9xx_i2c_xfer_msg(struct xlp9xx_i2c_dev *priv, struct i2c_msg *msg,
			       int last_msg)
{
	unsigned long timeleft;
	u32 intr_mask, cmd, val;

	priv->msg_buf = msg->buf;
	priv->msg_buf_remaining = priv->msg_len = msg->len;
	priv->msg_err = 0;
	priv->msg_read = (msg->flags & I2C_M_RD);
	reinit_completion(&priv->msg_complete);


	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_MFIFOCTRL,
			     XLP9XX_I2C_MFIFOCTRL_RST);


	if (priv->msg_read)
		xlp9xx_i2c_update_rx_fifo_thres(priv);


	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_SLAVEADDR,
			     (msg->addr << XLP9XX_I2C_SLAVEADDR_ADDR_SHIFT) |
			     (priv->msg_read ? XLP9XX_I2C_SLAVEADDR_RW : 0));


	val = xlp9xx_read_i2c_reg(priv, XLP9XX_I2C_CTRL);
	if (!priv->msg_read)
		val &= ~XLP9XX_I2C_CTRL_FIFORD;
	else
		val |= XLP9XX_I2C_CTRL_FIFORD;

	if (msg->flags & I2C_M_TEN)
		val |= XLP9XX_I2C_CTRL_ADDMODE;
	else
		val &= ~XLP9XX_I2C_CTRL_ADDMODE;


	val = (val & ~XLP9XX_I2C_CTRL_MCTLEN_MASK) |
	      (msg->len << XLP9XX_I2C_CTRL_MCTLEN_SHIFT);
	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_CTRL, val);


	if (!priv->msg_read)
		xlp9xx_i2c_fill_tx_fifo(priv);


	intr_mask = (XLP9XX_I2C_INTEN_ARLOST | XLP9XX_I2C_INTEN_BUSERR |
		     XLP9XX_I2C_INTEN_NACKADDR | XLP9XX_I2C_INTEN_DATADONE);

	if (priv->msg_read) {
		intr_mask |= XLP9XX_I2C_INTEN_MFIFOHI;
		if (msg->len == 0)
			intr_mask |= XLP9XX_I2C_INTEN_SADDR;
	} else {
		if (msg->len == 0)
			intr_mask |= XLP9XX_I2C_INTEN_SADDR;
		else
			intr_mask |= XLP9XX_I2C_INTEN_MFIFOEMTY;
	}
	xlp9xx_i2c_unmask_irq(priv, intr_mask);


	cmd = XLP9XX_I2C_CMD_START;
	cmd |= (priv->msg_read ? XLP9XX_I2C_CMD_READ : XLP9XX_I2C_CMD_WRITE);
	if (last_msg)
		cmd |= XLP9XX_I2C_CMD_STOP;

	xlp9xx_write_i2c_reg(priv, XLP9XX_I2C_CMD, cmd);

	timeleft = msecs_to_jiffies(XLP9XX_I2C_TIMEOUT_MS);
	timeleft = wait_for_completion_timeout(&priv->msg_complete, timeleft);

	if (priv->msg_err) {
		dev_dbg(priv->dev, "transfer error %x!\n", priv->msg_err);
		if (priv->msg_err & XLP9XX_I2C_INTEN_BUSERR)
			xlp9xx_i2c_init(priv);
		return -EIO;
	}

	if (timeleft == 0) {
		dev_dbg(priv->dev, "i2c transfer timed out!\n");
		xlp9xx_i2c_init(priv);
		return -ETIMEDOUT;
	}

	return 0;
}
