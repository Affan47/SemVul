set_happy_link_modes(struct happy_meal *hp, void __iomem *tregs)
{
	int full;


	if (hp->timer_state == arbwait) {
		hp->sw_lpa = happy_meal_tcvr_read(hp, tregs, MII_LPA);
		if (!(hp->sw_lpa & (LPA_10HALF | LPA_10FULL | LPA_100HALF | LPA_100FULL)))
			goto no_response;
		if (hp->sw_lpa & LPA_100FULL)
			full = 1;
		else if (hp->sw_lpa & LPA_100HALF)
			full = 0;
		else if (hp->sw_lpa & LPA_10FULL)
			full = 1;
		else
			full = 0;
	} else {

		hp->sw_bmcr = happy_meal_tcvr_read(hp, tregs, MII_BMCR);
		if (hp->sw_bmcr & BMCR_FULLDPLX)
			full = 1;
		else
			full = 0;
	}


	hme_write32(hp, hp->bigmacregs + BMAC_TXCFG,
		    hme_read32(hp, hp->bigmacregs + BMAC_TXCFG) &
		    ~(BIGMAC_TXCFG_ENABLE));
	while (hme_read32(hp, hp->bigmacregs + BMAC_TXCFG) & BIGMAC_TXCFG_ENABLE)
		barrier();
	if (full) {
		hp->happy_flags |= HFLAG_FULL;
		hme_write32(hp, hp->bigmacregs + BMAC_TXCFG,
			    hme_read32(hp, hp->bigmacregs + BMAC_TXCFG) |
			    BIGMAC_TXCFG_FULLDPLX);
	} else {
		hp->happy_flags &= ~(HFLAG_FULL);
		hme_write32(hp, hp->bigmacregs + BMAC_TXCFG,
			    hme_read32(hp, hp->bigmacregs + BMAC_TXCFG) &
			    ~(BIGMAC_TXCFG_FULLDPLX));
	}
	hme_write32(hp, hp->bigmacregs + BMAC_TXCFG,
		    hme_read32(hp, hp->bigmacregs + BMAC_TXCFG) |
		    BIGMAC_TXCFG_ENABLE);
	return 0;
no_response:
	return 1;
}
