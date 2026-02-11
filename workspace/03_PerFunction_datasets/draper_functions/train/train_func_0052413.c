sb_setmixer(sb_devc * devc, unsigned int port, unsigned int value)
{
	unsigned long flags;

	if (devc->model == MDL_ESS) {
		ess_setmixer (devc, port, value);
		return;
	}

	spin_lock_irqsave(&devc->lock, flags);

	outb(((unsigned char) (port & 0xff)), MIXER_ADDR);
	udelay(20);
	outb(((unsigned char) (value & 0xff)), MIXER_DATA);
	udelay(20);

	spin_unlock_irqrestore(&devc->lock, flags);
}
