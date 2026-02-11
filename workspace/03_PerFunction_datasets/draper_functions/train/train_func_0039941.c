wm8776_input_vol_put(struct snd_kcontrol *ctl,
				struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct xonar_wm87x6 *data = chip->model_data;
	int changed = 0;

	mutex_lock(&chip->mutex);
	changed = (value->value.integer.value[0] !=
		   (data->wm8776_regs[WM8776_ADCLVOL] & WM8776_AGMASK)) ||
		  (value->value.integer.value[1] !=
		   (data->wm8776_regs[WM8776_ADCRVOL] & WM8776_AGMASK));
	wm8776_write_cached(chip, WM8776_ADCLVOL,
			    value->value.integer.value[0] | WM8776_ZCA);
	wm8776_write_cached(chip, WM8776_ADCRVOL,
			    value->value.integer.value[1] | WM8776_ZCA);
	mutex_unlock(&chip->mutex);
	return changed;
}
