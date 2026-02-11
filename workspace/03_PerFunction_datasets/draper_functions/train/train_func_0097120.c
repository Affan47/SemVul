snd_soc_dapm_set_pin(struct snd_soc_dapm_context *dapm,
				const char *pin, int status)
{
	struct snd_soc_dapm_widget *w = dapm_find_widget(dapm, pin, true);

	dapm_assert_locked(dapm);

	if (!w) {
		dev_err(dapm->dev, "ASoC: DAPM unknown pin %s\n", pin);
		return -EINVAL;
	}

	if (w->connected != status) {
		dapm_mark_dirty(w, "pin configuration");
		dapm_widget_invalidate_input_paths(w);
		dapm_widget_invalidate_output_paths(w);
	}

	w->connected = status;
	if (status == 0)
		w->force = 0;

	return 0;
}
