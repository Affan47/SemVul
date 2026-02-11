em28xx_dvb_bus_ctrl(struct dvb_frontend *fe, int acquire)
{
	struct em28xx_i2c_bus *i2c_bus = fe->dvb->priv;
	struct em28xx *dev = i2c_bus->dev;

	if (acquire)
		return em28xx_set_mode(dev, EM28XX_DIGITAL_MODE);
	else
		return em28xx_set_mode(dev, EM28XX_SUSPEND);
}
