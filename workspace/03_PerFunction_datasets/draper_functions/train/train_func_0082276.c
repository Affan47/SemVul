serio_interrupt(struct serio *serio,
		unsigned char data, unsigned int dfl)
{
	unsigned long flags;
	irqreturn_t ret = IRQ_NONE;

	spin_lock_irqsave(&serio->lock, flags);

        if (likely(serio->drv)) {
                ret = serio->drv->interrupt(serio, data, dfl);
	} else if (!dfl && device_is_registered(&serio->dev)) {
		serio_rescan(serio);
		ret = IRQ_HANDLED;
	}

	spin_unlock_irqrestore(&serio->lock, flags);

	return ret;
}
