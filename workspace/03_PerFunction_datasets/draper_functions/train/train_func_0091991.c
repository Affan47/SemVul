ad1848_tmr_disable(int dev)
{
	unsigned long   flags;
	ad1848_info    *devc = (ad1848_info *) audio_devs[dev]->devc;

	spin_lock_irqsave(&devc->lock,flags);
	ad_write(devc, 16, ad_read(devc, 16) & ~0x40);
	devc->timer_running = 0;
	spin_unlock_irqrestore(&devc->lock,flags);
}
