set_timeout(struct cyclades_port *info, unsigned long value)
{
	struct cyclades_card *card = info->card;
	unsigned long flags;

	if (!cy_is_Z(card)) {
		spin_lock_irqsave(&card->card_lock, flags);
		cyy_writeb(info, CyRTPR, value & 0xff);
		spin_unlock_irqrestore(&card->card_lock, flags);
	}
	return 0;
}
