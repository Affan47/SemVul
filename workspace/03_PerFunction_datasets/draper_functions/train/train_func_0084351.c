xonar_ds_handle_hp_jack(struct oxygen *chip)
{
	struct xonar_wm87x6 *data = chip->model_data;
	bool hp_plugged;
	unsigned int reg;

	mutex_lock(&chip->mutex);

	hp_plugged = !(oxygen_read16(chip, OXYGEN_GPIO_DATA) &
		       GPIO_DS_HP_DETECT);

	oxygen_write16_masked(chip, OXYGEN_GPIO_DATA,
			      hp_plugged ? 0 : GPIO_DS_OUTPUT_FRONTLR,
			      GPIO_DS_OUTPUT_FRONTLR);

	reg = data->wm8766_regs[WM8766_DAC_CTRL] & ~WM8766_MUTEALL;
	if (hp_plugged)
		reg |= WM8766_MUTEALL;
	wm8766_write_cached(chip, WM8766_DAC_CTRL, reg);

	snd_jack_report(data->hp_jack, hp_plugged ? SND_JACK_HEADPHONE : 0);

	mutex_unlock(&chip->mutex);
}
