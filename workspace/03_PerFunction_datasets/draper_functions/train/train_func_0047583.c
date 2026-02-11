pdacf_suspend(struct pcmcia_device *link)
{
	struct snd_pdacf *chip = link->priv;

	snd_printdd(KERN_DEBUG "SUSPEND\n");
	if (chip) {
		snd_printdd(KERN_DEBUG "snd_pdacf_suspend calling\n");
		snd_pdacf_suspend(chip);
	}

	return 0;
}
