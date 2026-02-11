filter_control_put(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_soc_kcontrol_codec(kcontrol);
	struct ab8500_codec_drvdata *drvdata = snd_soc_codec_get_drvdata(codec);
	struct filter_control *fc =
			(struct filter_control *)kcontrol->private_value;
	unsigned int i;

	mutex_lock(&drvdata->ctrl_lock);
	for (i = 0; i < fc->count; i++)
		fc->value[i] = ucontrol->value.integer.value[i];
	mutex_unlock(&drvdata->ctrl_lock);

	return 0;
}
