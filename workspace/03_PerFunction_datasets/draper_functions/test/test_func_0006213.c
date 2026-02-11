init_card(struct w6692_hw *card)
{
	int	cnt = 3;
	u_long	flags;

	spin_lock_irqsave(&card->lock, flags);
	disable_hwirq(card);
	spin_unlock_irqrestore(&card->lock, flags);
	if (request_irq(card->irq, w6692_irq, IRQF_SHARED, card->name, card)) {
		pr_info("%s: couldn't get interrupt %d\n", card->name,
			card->irq);
		return -EIO;
	}
	while (cnt--) {
		spin_lock_irqsave(&card->lock, flags);
		initW6692(card);
		enable_hwirq(card);
		spin_unlock_irqrestore(&card->lock, flags);

		msleep_interruptible(10);
		if (debug & DEBUG_HW)
			pr_notice("%s: IRQ %d count %d\n", card->name,
				  card->irq, card->irqcnt);
		if (!card->irqcnt) {
			pr_info("%s: IRQ(%d) getting no IRQs during init %d\n",
				card->name, card->irq, 3 - cnt);
			reset_w6692(card);
		} else
			return 0;
	}
	free_irq(card->irq, card);
	return -EIO;
}
