update_wm8766_center_lfe_mix(struct oxygen *chip, bool mixed)
{
	struct xonar_wm87x6 *data = chip->model_data;
	unsigned int reg;


	reg = data->wm8766_regs[WM8766_DAC_CTRL] &
		~(WM8766_PL_LEFT_MASK | WM8766_PL_RIGHT_MASK);
	if (mixed)
		reg |= WM8766_PL_LEFT_LRMIX | WM8766_PL_RIGHT_LRMIX;
	else
		reg |= WM8766_PL_LEFT_LEFT | WM8766_PL_RIGHT_RIGHT;
	wm8766_write_cached(chip, WM8766_DAC_CTRL, reg);
}
