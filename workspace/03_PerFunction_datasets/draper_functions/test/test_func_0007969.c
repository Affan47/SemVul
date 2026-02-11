change_tst(struct idt77252_dev *card, struct vc_map *vc,
	   int n, unsigned int opc)
{
	unsigned long flags;
	int res;

	spin_lock_irqsave(&card->tst_lock, flags);

	__clear_tst(card, vc);
	res = __fill_tst(card, vc, n, opc);

	set_bit(TST_SWITCH_PENDING, &card->tst_state);
	if (!timer_pending(&card->tst_timer))
		mod_timer(&card->tst_timer, jiffies + 1);

	spin_unlock_irqrestore(&card->tst_lock, flags);
	return res;
}
