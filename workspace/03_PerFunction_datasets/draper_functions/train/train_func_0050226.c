sgdma_txbusy(struct altera_tse_private *priv)
{
	int delay = 0;


	while ((csrrd32(priv->tx_dma_csr, sgdma_csroffs(status))
		& SGDMA_STSREG_BUSY) && (delay++ < 100))
		udelay(1);

	if (csrrd32(priv->tx_dma_csr, sgdma_csroffs(status))
	    & SGDMA_STSREG_BUSY) {
		netdev_err(priv->dev, "timeout waiting for tx dma\n");
		return 1;
	}
	return 0;
}
