snd_ice1712_set_pro_rate(struct snd_ice1712 *ice, unsigned int rate, int force)
{
	unsigned long flags;
	unsigned char val, old;
	unsigned int i;

	switch (rate) {
	case 8000: val = 6; break;
	case 9600: val = 3; break;
	case 11025: val = 10; break;
	case 12000: val = 2; break;
	case 16000: val = 5; break;
	case 22050: val = 9; break;
	case 24000: val = 1; break;
	case 32000: val = 4; break;
	case 44100: val = 8; break;
	case 48000: val = 0; break;
	case 64000: val = 15; break;
	case 88200: val = 11; break;
	case 96000: val = 7; break;
	default:
		snd_BUG();
		val = 0;
		rate = 48000;
		break;
	}

	spin_lock_irqsave(&ice->reg_lock, flags);
	if (inb(ICEMT(ice, PLAYBACK_CONTROL)) & (ICE1712_CAPTURE_START_SHADOW|
						 ICE1712_PLAYBACK_PAUSE|
						 ICE1712_PLAYBACK_START)) {
__out:
		spin_unlock_irqrestore(&ice->reg_lock, flags);
		return;
	}
	if (!force && is_pro_rate_locked(ice))
		goto __out;

	old = inb(ICEMT(ice, RATE));
	if (!force && old == val)
		goto __out;

	ice->cur_rate = rate;
	outb(val, ICEMT(ice, RATE));
	spin_unlock_irqrestore(&ice->reg_lock, flags);

	if (ice->gpio.set_pro_rate)
		ice->gpio.set_pro_rate(ice, rate);
	for (i = 0; i < ice->akm_codecs; i++) {
		if (ice->akm[i].ops.set_rate_val)
			ice->akm[i].ops.set_rate_val(&ice->akm[i], rate);
	}
	if (ice->spdif.ops.setup_rate)
		ice->spdif.ops.setup_rate(ice, rate);
}
