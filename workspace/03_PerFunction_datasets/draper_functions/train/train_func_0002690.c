snd_wm8776_set_agc(struct snd_wm8776 *wm, u16 agc, u16 nothing)
{
	u16 alc1 = wm->regs[WM8776_REG_ALCCTRL1] & ~WM8776_ALC1_LCT_MASK;
	u16 alc2 = wm->regs[WM8776_REG_ALCCTRL2] & ~WM8776_ALC2_LCEN;

	switch (agc) {
	case 0:
		wm->agc_mode = WM8776_AGC_OFF;
		break;
	case 1:
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_LIM;
		break;
	case 2:
		alc1 |= WM8776_ALC1_LCSEL_ALCR;
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_ALC_R;
		break;
	case 3:
		alc1 |= WM8776_ALC1_LCSEL_ALCL;
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_ALC_L;
		break;
	case 4:
		alc1 |= WM8776_ALC1_LCSEL_ALCSTEREO;
		alc2 |= WM8776_ALC2_LCEN;
		wm->agc_mode = WM8776_AGC_ALC_STEREO;
		break;
	}
	snd_wm8776_write(wm, WM8776_REG_ALCCTRL1, alc1);
	snd_wm8776_write(wm, WM8776_REG_ALCCTRL2, alc2);
	snd_wm8776_update_agc_ctl(wm);
}
