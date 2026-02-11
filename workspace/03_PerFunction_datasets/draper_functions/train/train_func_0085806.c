bnxt_setup_msix(struct bnxt *bp)
{
	const int len = sizeof(bp->irq_tbl[0].name);
	struct net_device *dev = bp->dev;
	int tcs, i;

	tcs = netdev_get_num_tc(dev);
	if (tcs > 1) {
		int i, off, count;

		for (i = 0; i < tcs; i++) {
			count = bp->tx_nr_rings_per_tc;
			off = i * count;
			netdev_set_tc_queue(dev, i, count, off);
		}
	}

	for (i = 0; i < bp->cp_nr_rings; i++) {
		char *attr;

		if (bp->flags & BNXT_FLAG_SHARED_RINGS)
			attr = "TxRx";
		else if (i < bp->rx_nr_rings)
			attr = "rx";
		else
			attr = "tx";

		snprintf(bp->irq_tbl[i].name, len, "%s-%s-%d", dev->name, attr,
			 i);
		bp->irq_tbl[i].handler = bnxt_msix;
	}
}
