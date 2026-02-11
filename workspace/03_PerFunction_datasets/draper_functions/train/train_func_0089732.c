snd_ice1712_ews88mt_chip_select(struct snd_ice1712 *ice, int chip_mask)
{
	struct ews_spec *spec = ice->spec;
	unsigned char data, ndata;

	if (snd_BUG_ON(chip_mask < 0 || chip_mask > 0x0f))
		return -EINVAL;
	snd_i2c_lock(ice->i2c);
	if (snd_i2c_readbytes(spec->i2cdevs[EWS_I2C_PCF2], &data, 1) != 1)
		goto __error;
	ndata = (data & 0xf0) | chip_mask;
	if (ndata != data)
		if (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_PCF2], &ndata, 1)
		    != 1)
			goto __error;
	snd_i2c_unlock(ice->i2c);
	return 0;

     __error:
	snd_i2c_unlock(ice->i2c);
	dev_err(ice->card->dev,
		"AK4524 chip select failed, check cable to the front module\n");
	return -EIO;
}
