snd_emu10k1_send_routing_put(struct snd_kcontrol *kcontrol,
                                        struct snd_ctl_elem_value *ucontrol)
{
	unsigned long flags;
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	struct snd_emu10k1_pcm_mixer *mix =
		&emu->pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	int change = 0, voice, idx, val;
	int num_efx = emu->audigy ? 8 : 4;
	int mask = emu->audigy ? 0x3f : 0x0f;

	spin_lock_irqsave(&emu->reg_lock, flags);
	for (voice = 0; voice < 3; voice++)
		for (idx = 0; idx < num_efx; idx++) {
			val = ucontrol->value.integer.value[(voice * num_efx) + idx] & mask;
			if (mix->send_routing[voice][idx] != val) {
				mix->send_routing[voice][idx] = val;
				change = 1;
			}
		}
	if (change && mix->epcm) {
		if (mix->epcm->voices[0] && mix->epcm->voices[1]) {
			update_emu10k1_fxrt(emu, mix->epcm->voices[0]->number,
					    &mix->send_routing[1][0]);
			update_emu10k1_fxrt(emu, mix->epcm->voices[1]->number,
					    &mix->send_routing[2][0]);
		} else if (mix->epcm->voices[0]) {
			update_emu10k1_fxrt(emu, mix->epcm->voices[0]->number,
					    &mix->send_routing[0][0]);
		}
	}
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	return change;
}
