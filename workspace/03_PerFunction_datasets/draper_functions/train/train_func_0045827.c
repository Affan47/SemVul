link_status_1g(struct niu *np, int *link_up_p)
{
	struct niu_link_config *lp = &np->link_config;
	unsigned long flags;
	int err;

	spin_lock_irqsave(&np->lock, flags);

	err = link_status_mii(np, link_up_p);
	lp->supported |= SUPPORTED_TP;
	lp->active_advertising |= ADVERTISED_TP;

	spin_unlock_irqrestore(&np->lock, flags);
	return err;
}
