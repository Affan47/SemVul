dapm_connect_mux(struct snd_soc_dapm_context *dapm,
	struct snd_soc_dapm_path *path, const char *control_name,
	struct snd_soc_dapm_widget *w)
{
	const struct snd_kcontrol_new *kcontrol = &w->kcontrol_news[0];
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int val, item;
	int i;

	if (e->reg != SND_SOC_NOPM) {
		soc_dapm_read(dapm, e->reg, &val);
		val = (val >> e->shift_l) & e->mask;
		item = snd_soc_enum_val_to_item(e, val);
	} else {


		item = 0;
	}

	for (i = 0; i < e->items; i++) {
		if (!(strcmp(control_name, e->texts[i]))) {
			path->name = e->texts[i];
			if (i == item)
				path->connect = 1;
			else
				path->connect = 0;
			return 0;
		}
	}

	return -ENODEV;
}
