suni_stop(struct atm_dev *dev)
{
	struct suni_priv **walk;
	unsigned long flags;


	spin_lock_irqsave(&sunis_lock,flags);
	for (walk = &sunis; *walk != PRIV(dev);
	    walk = &PRIV((*walk)->dev)->next);
	*walk = PRIV((*walk)->dev)->next;
	if (!sunis) del_timer_sync(&poll_timer);
	spin_unlock_irqrestore(&sunis_lock,flags);
	kfree(PRIV(dev));

	return 0;
}
