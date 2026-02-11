dc_servo_cmd(struct snd_soc_codec *codec,
			 unsigned int reg, unsigned int val, unsigned int mask)
{
	int timeout = 10;

	dev_dbg(codec->dev, "%s: reg = %#x, val = %#x, mask = %#x\n",
		__func__, reg, val, mask);

	snd_soc_write(codec, reg, val);
	while (timeout--) {
		msleep(10);
		val = snd_soc_read(codec, WM8995_DC_SERVO_READBACK_0);
		if ((val & mask) == mask)
			return;
	}

	dev_err(codec->dev, "Timed out waiting for DC Servo\n");
}
