wait_for_dc_servo(struct snd_soc_codec *codec, unsigned int op)
{
	struct wm_hubs_data *hubs = snd_soc_codec_get_drvdata(codec);
	unsigned int reg;
	int count = 0;
	int timeout;
	unsigned int val;

	val = op | WM8993_DCS_ENA_CHAN_0 | WM8993_DCS_ENA_CHAN_1;


	snd_soc_write(codec, WM8993_DC_SERVO_0, val);

	dev_dbg(codec->dev, "Waiting for DC servo...\n");

	if (hubs->dcs_done_irq)
		timeout = 4;
	else
		timeout = 400;

	do {
		count++;

		if (hubs->dcs_done_irq)
			wait_for_completion_timeout(&hubs->dcs_done,
						    msecs_to_jiffies(250));
		else
			msleep(1);

		reg = snd_soc_read(codec, WM8993_DC_SERVO_0);
		dev_dbg(codec->dev, "DC servo: %x\n", reg);
	} while (reg & op && count < timeout);

	if (reg & op)
		dev_err(codec->dev, "Timed out waiting for DC Servo %x\n",
			op);
}
