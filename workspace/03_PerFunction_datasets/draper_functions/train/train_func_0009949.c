rhine_kick_tx_threshold(struct rhine_private *rp)
{
	if (rp->tx_thresh < 0xe0) {
		void __iomem *ioaddr = rp->base;

		rp->tx_thresh += 0x20;
		BYTE_REG_BITS_SET(rp->tx_thresh, 0x80, ioaddr + TxConfig);
	}
}
