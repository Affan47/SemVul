port_has_10g(struct phy_probe_info *p, int port)
{
	int i;

	for (i = 0; i < p->cur[PHY_TYPE_PMA_PMD]; i++) {
		if (p->phy_port[PHY_TYPE_PMA_PMD][i] == port)
			return 1;
	}
	for (i = 0; i < p->cur[PHY_TYPE_PCS]; i++) {
		if (p->phy_port[PHY_TYPE_PCS][i] == port)
			return 1;
	}

	return 0;
}
