arizona_spk_ev(struct snd_soc_dapm_widget *w,
			  struct snd_kcontrol *kcontrol,
			  int event)
{
	struct snd_soc_codec *codec = snd_soc_dapm_to_codec(w->dapm);
	struct arizona *arizona = dev_get_drvdata(codec->dev->parent);
	struct arizona_priv *priv = snd_soc_codec_get_drvdata(codec);
	bool manual_ena = false;
	int val;

	switch (arizona->type) {
	case WM5102:
		switch (arizona->rev) {
		case 0:
			break;
		default:
			manual_ena = true;
			break;
		}
	default:
		break;
	}

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (!priv->spk_ena && manual_ena) {
			regmap_write_async(arizona->regmap, 0x4f5, 0x25a);
			priv->spk_ena_pending = true;
		}
		break;
	case SND_SOC_DAPM_POST_PMU:
		val = snd_soc_read(codec, ARIZONA_INTERRUPT_RAW_STATUS_3);
		if (val & ARIZONA_SPK_OVERHEAT_STS) {
			dev_crit(arizona->dev,
				 "Speaker not enabled due to temperature\n");
			return -EBUSY;
		}

		regmap_update_bits_async(arizona->regmap,
					 ARIZONA_OUTPUT_ENABLES_1,
					 1 << w->shift, 1 << w->shift);

		if (priv->spk_ena_pending) {
			msleep(75);
			regmap_write_async(arizona->regmap, 0x4f5, 0xda);
			priv->spk_ena_pending = false;
			priv->spk_ena++;
		}
		break;
	case SND_SOC_DAPM_PRE_PMD:
		if (manual_ena) {
			priv->spk_ena--;
			if (!priv->spk_ena)
				regmap_write_async(arizona->regmap,
						   0x4f5, 0x25a);
		}

		regmap_update_bits_async(arizona->regmap,
					 ARIZONA_OUTPUT_ENABLES_1,
					 1 << w->shift, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		if (manual_ena) {
			if (!priv->spk_ena)
				regmap_write_async(arizona->regmap,
						   0x4f5, 0x0da);
		}
		break;
	default:
		break;
	}

	return 0;
}
