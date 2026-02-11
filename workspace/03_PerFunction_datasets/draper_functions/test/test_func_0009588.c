rhine_restart_tx(struct net_device *dev) {
	struct rhine_private *rp = netdev_priv(dev);
	void __iomem *ioaddr = rp->base;
	int entry = rp->dirty_tx % TX_RING_SIZE;
	u32 intr_status;


	intr_status = rhine_get_events(rp);

	if ((intr_status & IntrTxErrSummary) == 0) {


		iowrite32(rp->tx_ring_dma + entry * sizeof(struct tx_desc),
		       ioaddr + TxRingPtr);

		iowrite8(ioread8(ioaddr + ChipCmd) | CmdTxOn,
		       ioaddr + ChipCmd);

		if (rp->tx_ring[entry].desc_length & cpu_to_le32(0x020000))

			BYTE_REG_BITS_ON(1 << 7, ioaddr + TQWake);

		iowrite8(ioread8(ioaddr + ChipCmd1) | Cmd1TxDemand,
		       ioaddr + ChipCmd1);
		IOSYNC;
	}
	else {

		netif_warn(rp, tx_err, dev, "another error occurred %08x\n",
			   intr_status);
	}

}
