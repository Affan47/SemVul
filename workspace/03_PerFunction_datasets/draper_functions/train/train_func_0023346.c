img_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			int num)
{
	struct img_i2c *i2c = i2c_get_adapdata(adap);
	bool atomic = false;
	int i, ret;
	unsigned long time_left;

	if (i2c->mode == MODE_SUSPEND) {
		WARN(1, "refusing to service transaction in suspended state\n");
		return -EIO;
	}

	if (i2c->mode == MODE_FATAL)
		return -EIO;

	for (i = 0; i < num; i++) {
		if (likely(msgs[i].len))
			continue;


		if (unlikely(msgs[i].flags & I2C_M_RD))
			return -EIO;


		atomic = true;
	}

	ret = clk_prepare_enable(i2c->scb_clk);
	if (ret)
		return ret;

	for (i = 0; i < num; i++) {
		struct i2c_msg *msg = &msgs[i];
		unsigned long flags;

		spin_lock_irqsave(&i2c->lock, flags);


		i2c->msg = *msg;
		i2c->msg_status = 0;


		i2c->last_msg = (i == num - 1);
		reinit_completion(&i2c->msg_complete);


		img_i2c_writel(i2c, SCB_INT_CLEAR_REG, ~0);
		img_i2c_writel(i2c, SCB_CLEAR_REG, ~0);

		if (atomic)
			img_i2c_atomic_start(i2c);
		else if (msg->flags & I2C_M_RD)
			img_i2c_read(i2c);
		else
			img_i2c_write(i2c);
		spin_unlock_irqrestore(&i2c->lock, flags);

		time_left = wait_for_completion_timeout(&i2c->msg_complete,
						      IMG_I2C_TIMEOUT);
		del_timer_sync(&i2c->check_timer);

		if (time_left == 0) {
			dev_err(adap->dev.parent, "i2c transfer timed out\n");
			i2c->msg_status = -ETIMEDOUT;
			break;
		}

		if (i2c->msg_status)
			break;
	}

	clk_disable_unprepare(i2c->scb_clk);

	return i2c->msg_status ? i2c->msg_status : num;
}
