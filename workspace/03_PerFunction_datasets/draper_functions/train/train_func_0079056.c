happy_meal_transceiver_check(struct happy_meal *hp, void __iomem *tregs)
{
	unsigned long tconfig = hme_read32(hp, tregs + TCVR_CFG);

	ASD(("happy_meal_transceiver_check: tcfg=%08lx ", tconfig));
	if (hp->happy_flags & HFLAG_POLL) {

		ASD(("<polling> "));
		if (hp->tcvr_type == internal) {
			if (tconfig & TCV_CFG_MDIO1) {
				ASD(("<internal> <poll stop> "));
				happy_meal_poll_stop(hp, tregs);
				hp->paddr = TCV_PADDR_ETX;
				hp->tcvr_type = external;
				ASD(("<external>\n"));
				tconfig &= ~(TCV_CFG_PENABLE);
				tconfig |= TCV_CFG_PSELECT;
				hme_write32(hp, tregs + TCVR_CFG, tconfig);
			}
		} else {
			if (hp->tcvr_type == external) {
				ASD(("<external> "));
				if (!(hme_read32(hp, tregs + TCVR_STATUS) >> 16)) {
					ASD(("<poll stop> "));
					happy_meal_poll_stop(hp, tregs);
					hp->paddr = TCV_PADDR_ITX;
					hp->tcvr_type = internal;
					ASD(("<internal>\n"));
					hme_write32(hp, tregs + TCVR_CFG,
						    hme_read32(hp, tregs + TCVR_CFG) &
						    ~(TCV_CFG_PSELECT));
				}
				ASD(("\n"));
			} else {
				ASD(("<none>\n"));
			}
		}
	} else {
		u32 reread = hme_read32(hp, tregs + TCVR_CFG);


		ASD(("<not polling> "));
		if (reread & TCV_CFG_MDIO1) {
			hme_write32(hp, tregs + TCVR_CFG, tconfig | TCV_CFG_PSELECT);
			hp->paddr = TCV_PADDR_ETX;
			hp->tcvr_type = external;
			ASD(("<external>\n"));
		} else {
			if (reread & TCV_CFG_MDIO0) {
				hme_write32(hp, tregs + TCVR_CFG,
					    tconfig & ~(TCV_CFG_PSELECT));
				hp->paddr = TCV_PADDR_ITX;
				hp->tcvr_type = internal;
				ASD(("<internal>\n"));
			} else {
				printk(KERN_ERR "happy meal: Transceiver and a coke please.");
				hp->tcvr_type = none;
				ASD(("<none>\n"));
			}
		}
	}
}
