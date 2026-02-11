amd8111e_poll_link(struct amd8111e_priv *lp)
{
	unsigned int status, speed;
	u32 reg_val;

	if (!lp->link) {

		amd8111e_read_phy(lp, lp->ext_phy_addr, MII_BMCR, &reg_val);
		amd8111e_read_phy(lp, lp->ext_phy_addr, MII_BMSR, &reg_val);
		amd8111e_read_phy(lp, lp->ext_phy_addr, MII_ADVERTISE, &reg_val);
		amd8111e_read_phy(lp, lp->ext_phy_addr, MII_LPA, &reg_val);
		status = readl(lp->mmio + STAT0);

		if (status & LINK_STATS) {
			lp->link = 1;
			speed = (status & SPEED_MASK) >> 7;
			if (speed == PHY_SPEED_100)
				lp->speed = 1;
			else
				lp->speed = 0;
			if (status & FULL_DPLX)
				lp->duplex = 1;
			else
				lp->duplex = 0;

			printf("Link is up: %s Mbps %s duplex\n",
				lp->speed ? "100" : "10", lp->duplex ? "full" : "half");
		}
	} else {
		status = readl(lp->mmio + STAT0);
		if (!(status & LINK_STATS)) {
			lp->link = 0;
			printf("Link is down\n");
		}
	}
}
