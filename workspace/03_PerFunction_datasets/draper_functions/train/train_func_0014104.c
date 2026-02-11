cp_event(struct snd_soc_dapm_widget *w,
		    struct snd_kcontrol *kcontrol, int event)
{
	if (WARN_ON(event != SND_SOC_DAPM_POST_PMU))
		return -EINVAL;


	udelay(500);

	return 0;
}
