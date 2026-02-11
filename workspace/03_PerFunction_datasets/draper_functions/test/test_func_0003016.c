mc13xxx_unlock(struct mc13xxx *mc13xxx)
{
	dev_dbg(mc13xxx->dev, "%s from %ps\n",
			__func__, __builtin_return_address(0));
	mutex_unlock(&mc13xxx->lock);
}
