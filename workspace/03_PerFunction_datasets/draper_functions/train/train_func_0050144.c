pm860x_codec_handler(int irq, void *data)
{
	struct pm860x_priv *pm860x = data;
	int status, shrt, report = 0, mic_report = 0;
	int mask;

	status = pm860x_reg_read(pm860x->i2c, REG_STATUS_1);
	shrt = pm860x_reg_read(pm860x->i2c, REG_SHORTS);
	mask = pm860x->det.hs_shrt | pm860x->det.hook_det | pm860x->det.lo_shrt
		| pm860x->det.hp_det;

#ifndef CONFIG_SND_SOC_88PM860X_MODULE
	if (status & (HEADSET_STATUS | MIC_STATUS | SHORT_HS1 | SHORT_HS2 |
		      SHORT_LO1 | SHORT_LO2))
		trace_snd_soc_jack_irq(dev_name(pm860x->codec->dev));
#endif

	if ((pm860x->det.hp_det & SND_JACK_HEADPHONE)
		&& (status & HEADSET_STATUS))
		report |= SND_JACK_HEADPHONE;

	if ((pm860x->det.mic_det & SND_JACK_MICROPHONE)
		&& (status & MIC_STATUS))
		mic_report |= SND_JACK_MICROPHONE;

	if (pm860x->det.hs_shrt && (shrt & (SHORT_HS1 | SHORT_HS2)))
		report |= pm860x->det.hs_shrt;

	if (pm860x->det.hook_det && (status & HOOK_STATUS))
		report |= pm860x->det.hook_det;

	if (pm860x->det.lo_shrt && (shrt & (SHORT_LO1 | SHORT_LO2)))
		report |= pm860x->det.lo_shrt;

	if (report)
		snd_soc_jack_report(pm860x->det.hp_jack, report, mask);
	if (mic_report)
		snd_soc_jack_report(pm860x->det.mic_jack, SND_JACK_MICROPHONE,
				    SND_JACK_MICROPHONE);

	dev_dbg(pm860x->codec->dev, "headphone report:0x%x, mask:%x\n",
		report, mask);
	dev_dbg(pm860x->codec->dev, "microphone report:0x%x\n", mic_report);
	return IRQ_HANDLED;
}
