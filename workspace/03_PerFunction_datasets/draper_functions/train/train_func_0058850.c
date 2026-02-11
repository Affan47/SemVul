ad1848_mixer_set_channel(ad1848_info *devc, int dev, int value, int channel)
{
	int regoffs, muteregoffs;
	unsigned char val, muteval;
	unsigned long flags;

	regoffs = devc->mix_devices[dev][channel].regno;
	muteregoffs = devc->mix_devices[dev][channel].mutereg;
	val = ad_read(devc, regoffs);

	if (muteregoffs != regoffs) {
		muteval = ad_read(devc, muteregoffs);
		oss_change_bits(devc, &val, &muteval, dev, channel, value);
	}
	else
		oss_change_bits(devc, &val, &val, dev, channel, value);

	spin_lock_irqsave(&devc->lock,flags);
	ad_write(devc, regoffs, val);
	devc->saved_regs[regoffs] = val;
	if (muteregoffs != regoffs) {
		ad_write(devc, muteregoffs, muteval);
		devc->saved_regs[muteregoffs] = muteval;
	}
	spin_unlock_irqrestore(&devc->lock,flags);
}
