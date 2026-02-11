sb1_audio_halt_xfer(int dev)
{
	unsigned long flags;
	sb_devc *devc = audio_devs[dev]->devc;

	spin_lock_irqsave(&devc->lock, flags);
	sb_dsp_reset(devc);
	spin_unlock_irqrestore(&devc->lock, flags);
}
