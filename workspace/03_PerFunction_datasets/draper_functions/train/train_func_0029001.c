link_status_10g_serdes(struct niu *np, int *link_up_p)
{
	unsigned long flags;
	struct niu_link_config *lp = &np->link_config;
	int link_up = 0;
	int link_ok = 1;
	u64 val, val2;
	u16 current_speed;
	u8 current_duplex;

	if (!(np->flags & NIU_FLAGS_10G))
		return link_status_1g_serdes(np, link_up_p);

	current_speed = SPEED_INVALID;
	current_duplex = DUPLEX_INVALID;
	spin_lock_irqsave(&np->lock, flags);

	val = nr64_xpcs(XPCS_STATUS(0));
	val2 = nr64_mac(XMAC_INTER2);
	if (val2 & 0x01000000)
		link_ok = 0;

	if ((val & 0x1000ULL) && link_ok) {
		link_up = 1;
		current_speed = SPEED_10000;
		current_duplex = DUPLEX_FULL;
	}
	lp->active_speed = current_speed;
	lp->active_duplex = current_duplex;
	spin_unlock_irqrestore(&np->lock, flags);
	*link_up_p = link_up;
	return 0;
}
