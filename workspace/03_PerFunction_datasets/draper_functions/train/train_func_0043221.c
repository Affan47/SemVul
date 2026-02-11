bfa_phy_get_stats(struct bfa_phy_s *phy, u8 instance,
		struct bfa_phy_stats_s *stats,
		bfa_cb_phy_t cbfn, void *cbarg)
{
	bfa_trc(phy, BFI_PHY_H2I_STATS_REQ);
	bfa_trc(phy, instance);

	if (!bfa_phy_present(phy))
		return BFA_STATUS_PHY_NOT_PRESENT;

	if (!bfa_ioc_is_operational(phy->ioc))
		return BFA_STATUS_IOC_NON_OP;

	if (phy->op_busy || bfa_phy_busy(phy->ioc)) {
		bfa_trc(phy, phy->op_busy);
		return BFA_STATUS_DEVBUSY;
	}

	phy->op_busy = 1;
	phy->cbfn = cbfn;
	phy->cbarg = cbarg;
	phy->instance = instance;
	phy->ubuf = (u8 *) stats;
	bfa_phy_stats_send(phy);

	return BFA_STATUS_OK;
}
