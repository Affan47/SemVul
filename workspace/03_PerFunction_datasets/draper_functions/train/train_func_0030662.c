xc4000_sleep(struct dvb_frontend *fe)
{
	struct xc4000_priv *priv = fe->tuner_priv;
	int	ret = 0;

	dprintk(1, "%s()\n", __func__);

	mutex_lock(&priv->lock);


	if ((no_poweroff == 2 ||
	     (no_poweroff == 0 && priv->default_pm != 0)) &&
	    (priv->cur_fw.type & BASE) != 0) {

		priv->cur_fw.type = XC_POWERED_DOWN;

		if (xc_write_reg(priv, XREG_POWER_DOWN, 0) != 0) {
			printk(KERN_ERR
			       "xc4000: %s() unable to shutdown tuner\n",
			       __func__);
			ret = -EREMOTEIO;
		}
		msleep(20);
	}

	mutex_unlock(&priv->lock);

	return ret;
}
