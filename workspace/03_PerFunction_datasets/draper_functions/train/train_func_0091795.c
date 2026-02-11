neo_drain(struct tty_struct *tty, uint seconds)
{
	unsigned long flags;
	struct channel_t *ch;
	struct un_t *un;
	int rc = 0;

	if (!tty || tty->magic != TTY_MAGIC)
		return -ENXIO;

	un = (struct un_t *)tty->driver_data;
	if (!un || un->magic != DGNC_UNIT_MAGIC)
		return -ENXIO;

	ch = un->un_ch;
	if (!ch || ch->magic != DGNC_CHANNEL_MAGIC)
		return -ENXIO;

	spin_lock_irqsave(&ch->ch_lock, flags);
	un->un_flags |= UN_EMPTY;
	spin_unlock_irqrestore(&ch->ch_lock, flags);


	rc = wait_event_interruptible(un->un_flags_wait, ((un->un_flags & UN_EMPTY) == 0));


	return rc;
}
