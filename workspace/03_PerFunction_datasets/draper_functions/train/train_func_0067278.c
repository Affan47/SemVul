snd_hdspm_midi_input_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct hdspm *hdspm;
	struct hdspm_midi *hmidi;
	unsigned long flags;

	hmidi = substream->rmidi->private_data;
	hdspm = hmidi->hdspm;

	spin_lock_irqsave (&hdspm->lock, flags);
	if (up) {
		if (!(hdspm->control_register & hmidi->ie)) {
			snd_hdspm_flush_midi_input (hdspm, hmidi->id);
			hdspm->control_register |= hmidi->ie;
		}
	} else {
		hdspm->control_register &= ~hmidi->ie;
	}

	hdspm_write(hdspm, HDSPM_controlRegister, hdspm->control_register);
	spin_unlock_irqrestore (&hdspm->lock, flags);
}
