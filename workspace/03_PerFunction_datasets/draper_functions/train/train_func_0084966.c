snd_ymfpci_voice_free(struct snd_ymfpci *chip, struct snd_ymfpci_voice *pvoice)
{
	unsigned long flags;

	if (snd_BUG_ON(!pvoice))
		return -EINVAL;
	snd_ymfpci_hw_stop(chip);
	spin_lock_irqsave(&chip->voice_lock, flags);
	if (pvoice->number == chip->src441_used) {
		chip->src441_used = -1;
		pvoice->ypcm->use_441_slot = 0;
	}
	pvoice->use = pvoice->pcm = pvoice->synth = pvoice->midi = 0;
	pvoice->ypcm = NULL;
	pvoice->interrupt = NULL;
	spin_unlock_irqrestore(&chip->voice_lock, flags);
	return 0;
}
