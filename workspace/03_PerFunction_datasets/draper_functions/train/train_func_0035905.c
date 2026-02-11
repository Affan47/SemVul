rt298_irq(int irq, void *data)
{
	struct rt298_priv *rt298 = data;
	bool hp = false;
	bool mic = false;
	int ret, status = 0;

	ret = rt298_jack_detect(rt298, &hp, &mic);


	regmap_update_bits(rt298->regmap, RT298_IRQ_CTRL, 0x1, 0x1);

	if (ret == 0) {
		if (hp == true)
			status |= SND_JACK_HEADPHONE;

		if (mic == true)
			status |= SND_JACK_MICROPHONE;

		snd_soc_jack_report(rt298->jack, status,
			SND_JACK_MICROPHONE | SND_JACK_HEADPHONE);

		pm_wakeup_event(&rt298->i2c->dev, 300);
	}

	return IRQ_HANDLED;
}
