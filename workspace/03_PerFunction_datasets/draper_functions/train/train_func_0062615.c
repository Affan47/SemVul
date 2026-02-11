snd_als300_interrupt(int irq, void *dev_id)
{
	u8 status;
	struct snd_als300 *chip = dev_id;
	struct snd_als300_substream_data *data;

	status = inb(chip->port+ALS300_IRQ_STATUS);
	if (!status)
		return IRQ_NONE;


	outb(status, chip->port+ALS300_IRQ_STATUS);
	if (status & IRQ_PLAYBACK) {
		if (chip->pcm && chip->playback_substream) {
			data = chip->playback_substream->runtime->private_data;
			data->period_flipflop ^= 1;
			snd_pcm_period_elapsed(chip->playback_substream);
			snd_als300_dbgplay("IRQ_PLAYBACK\n");
		}
	}
	if (status & IRQ_CAPTURE) {
		if (chip->pcm && chip->capture_substream) {
			data = chip->capture_substream->runtime->private_data;
			data->period_flipflop ^= 1;
			snd_pcm_period_elapsed(chip->capture_substream);
			snd_als300_dbgplay("IRQ_CAPTURE\n");
		}
	}
	return IRQ_HANDLED;
}
