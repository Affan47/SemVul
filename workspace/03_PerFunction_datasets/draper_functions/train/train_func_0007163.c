tegra_wm8903_event_hp(struct snd_soc_dapm_widget *w,
					struct snd_kcontrol *k, int event)
{
	struct snd_soc_dapm_context *dapm = w->dapm;
	struct snd_soc_card *card = dapm->card;
	struct tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);

	if (!gpio_is_valid(machine->gpio_hp_mute))
		return 0;

	gpio_set_value_cansleep(machine->gpio_hp_mute,
				!SND_SOC_DAPM_EVENT_ON(event));

	return 0;
}
