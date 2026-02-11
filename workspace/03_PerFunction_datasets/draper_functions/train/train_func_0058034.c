da7219_tonegen_freq_get(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_soc_kcontrol_codec(kcontrol);
	struct da7219_priv *da7219 = snd_soc_codec_get_drvdata(codec);
	struct soc_mixer_control *mixer_ctrl =
		(struct soc_mixer_control *) kcontrol->private_value;
	unsigned int reg = mixer_ctrl->reg;
	u16 val;
	int ret;

	mutex_lock(&da7219->lock);
	ret = regmap_raw_read(da7219->regmap, reg, &val, sizeof(val));
	mutex_unlock(&da7219->lock);

	if (ret)
		return ret;


	ucontrol->value.integer.value[0] = le16_to_cpu(val);

	return 0;
}
