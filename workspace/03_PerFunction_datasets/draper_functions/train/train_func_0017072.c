dwceqos_set_tx_flowcontrol(struct net_local *lp, bool enable)
{
	u32 regval;
	unsigned long flags;

	spin_lock_irqsave(&lp->hw_lock, flags);


	regval = dwceqos_read(lp, REG_DWCEQOS_MTL_RXQ0_OPER);
	if (enable)
		regval |= DWCEQOS_MTL_RXQ_EHFC;
	else
		regval &= ~DWCEQOS_MTL_RXQ_EHFC;

	dwceqos_write(lp, REG_DWCEQOS_MTL_RXQ0_OPER, regval);


	regval = dwceqos_read(lp, REG_DWCEQOS_MAC_Q0_TX_FLOW);
	if (enable)
		regval |= DWCEQOS_MAC_Q0_TX_FLOW_TFE;
	else
		regval &= ~DWCEQOS_MAC_Q0_TX_FLOW_TFE;
	dwceqos_write(lp, REG_DWCEQOS_MAC_Q0_TX_FLOW, regval);

	spin_unlock_irqrestore(&lp->hw_lock, flags);
}
