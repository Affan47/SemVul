wm8996_hpdet_irq(struct snd_soc_codec *codec)
{
	struct snd_soc_dapm_context *dapm = snd_soc_codec_get_dapm(codec);
	struct wm8996_priv *wm8996 = snd_soc_codec_get_drvdata(codec);
	int val, reg, report;


	report = SND_JACK_HEADPHONE;

	reg = snd_soc_read(codec, WM8996_HEADPHONE_DETECT_2);
	if (reg < 0) {
		dev_err(codec->dev, "Failed to read HPDET status\n");
		goto out;
	}

	if (!(reg & WM8996_HP_DONE)) {
		dev_err(codec->dev, "Got HPDET IRQ but HPDET is busy\n");
		goto out;
	}

	val = reg & WM8996_HP_LVL_MASK;

	dev_dbg(codec->dev, "HPDET measured %d ohms\n", val);


	if (val >= 126)
		report = SND_JACK_LINEOUT;
	else
		report = SND_JACK_HEADPHONE;

out:
	if (wm8996->jack_mic)
		report |= SND_JACK_MICROPHONE;

	snd_soc_jack_report(wm8996->jack, report,
			    SND_JACK_LINEOUT | SND_JACK_HEADSET);

	wm8996->detecting = false;


	if (!(snd_soc_read(codec, WM8996_POWER_MANAGEMENT_1) &
	      (WM8996_HPOUT1L_ENA | WM8996_HPOUT1R_RMV_SHORT)))
		snd_soc_update_bits(codec, WM8996_ANALOGUE_HP_1,
				    WM8996_HPOUT1L_RMV_SHORT |
				    WM8996_HPOUT1R_RMV_SHORT, 0);


	snd_soc_update_bits(codec, WM8996_ACCESSORY_DETECT_MODE_1,
			    WM8996_JD_MODE_MASK, 0);
	snd_soc_update_bits(codec, WM8996_MIC_DETECT_1, WM8996_MICD_ENA,
			    WM8996_MICD_ENA);

	snd_soc_dapm_disable_pin(dapm, "Bandgap");
	snd_soc_dapm_sync(dapm);
}
