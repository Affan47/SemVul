snd_hdsp_midi_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct hdsp_midi *hmidi;
	unsigned long flags;

	hmidi = (struct hdsp_midi *) substream->rmidi->private_data;
	spin_lock_irqsave (&hmidi->lock, flags);
	if (up) {
		if (!hmidi->istimer) {
			setup_timer(&hmidi->timer, snd_hdsp_midi_output_timer,
				    (unsigned long) hmidi);
			mod_timer(&hmidi->timer, 1 + jiffies);
			hmidi->istimer++;
		}
	} else {
		if (hmidi->istimer && --hmidi->istimer <= 0)
			del_timer (&hmidi->timer);
	}
	spin_unlock_irqrestore (&hmidi->lock, flags);
	if (up)
		snd_hdsp_midi_output_write(hmidi);
}
