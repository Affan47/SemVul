midi_capture_trigger(struct snd_rawmidi_substream *substrm, int up)
{
	struct snd_tscm *tscm = substrm->rmidi->private_data;
	unsigned long flags;

	spin_lock_irqsave(&tscm->lock, flags);

	if (up)
		tscm->tx_midi_substreams[substrm->number] = substrm;
	else
		tscm->tx_midi_substreams[substrm->number] = NULL;

	spin_unlock_irqrestore(&tscm->lock, flags);
}
