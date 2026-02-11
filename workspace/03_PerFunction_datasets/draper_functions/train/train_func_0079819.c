pxa168_eth_collect_events(struct pxa168_eth_private *pep,
				     struct net_device *dev)
{
	u32 icr;
	int ret = 0;

	icr = rdl(pep, INT_CAUSE);
	if (icr == 0)
		return IRQ_NONE;

	wrl(pep, INT_CAUSE, ~icr);
	if (icr & (ICR_TXBUF_H | ICR_TXBUF_L)) {
		pep->work_todo |= WORK_TX_DONE;
		ret = 1;
	}
	if (icr & ICR_RXBUF)
		ret = 1;
	return ret;
}
