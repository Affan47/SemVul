rhine_tx_err(struct rhine_private *rp, u32 status)
{
	struct net_device *dev = rp->dev;

	if (status & IntrTxAborted) {
		netif_info(rp, tx_err, dev,
			   "Abort %08x, frame dropped\n", status);
	}

	if (status & IntrTxUnderrun) {
		rhine_kick_tx_threshold(rp);
		netif_info(rp, tx_err ,dev, "Transmitter underrun, "
			   "Tx threshold now %02x\n", rp->tx_thresh);
	}

	if (status & IntrTxDescRace)
		netif_info(rp, tx_err, dev, "Tx descriptor write-back race\n");

	if ((status & IntrTxError) &&
	    (status & (IntrTxAborted | IntrTxUnderrun | IntrTxDescRace)) == 0) {
		rhine_kick_tx_threshold(rp);
		netif_info(rp, tx_err, dev, "Unspecified error. "
			   "Tx threshold now %02x\n", rp->tx_thresh);
	}

	rhine_restart_tx(dev);
}
