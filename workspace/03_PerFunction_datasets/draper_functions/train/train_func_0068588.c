bnx2_phy_get_pause_adv(struct bnx2 *bp)
{
	u32 adv = 0;

	if ((bp->req_flow_ctrl & (FLOW_CTRL_RX | FLOW_CTRL_TX)) ==
		(FLOW_CTRL_RX | FLOW_CTRL_TX)) {

		if (bp->phy_flags & PHY_SERDES_FLAG) {
			adv = ADVERTISE_1000XPAUSE;
		}
		else {
			adv = ADVERTISE_PAUSE_CAP;
		}
	}
	else if (bp->req_flow_ctrl & FLOW_CTRL_TX) {
		if (bp->phy_flags & PHY_SERDES_FLAG) {
			adv = ADVERTISE_1000XPSE_ASYM;
		}
		else {
			adv = ADVERTISE_PAUSE_ASYM;
		}
	}
	else if (bp->req_flow_ctrl & FLOW_CTRL_RX) {
		if (bp->phy_flags & PHY_SERDES_FLAG) {
			adv = ADVERTISE_1000XPAUSE | ADVERTISE_1000XPSE_ASYM;
		}
		else {
			adv = ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
		}
	}
	return adv;
}
