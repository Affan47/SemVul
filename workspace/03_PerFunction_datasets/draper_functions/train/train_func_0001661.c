img_i2c_reset_bus(struct img_i2c *i2c)
{
	unsigned long flags;
	unsigned long time_left;

	spin_lock_irqsave(&i2c->lock, flags);
	reinit_completion(&i2c->msg_complete);
	img_i2c_reset_start(i2c);
	spin_unlock_irqrestore(&i2c->lock, flags);

	time_left = wait_for_completion_timeout(&i2c->msg_complete,
					      IMG_I2C_TIMEOUT);
	if (time_left == 0)
		return -ETIMEDOUT;
	return 0;
}
