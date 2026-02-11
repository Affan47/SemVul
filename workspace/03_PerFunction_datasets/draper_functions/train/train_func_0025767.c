xcan_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = (struct net_device *)dev_id;
	struct xcan_priv *priv = netdev_priv(ndev);
	u32 isr, ier;


	isr = priv->read_reg(priv, XCAN_ISR_OFFSET);
	if (!isr)
		return IRQ_NONE;


	if (isr & (XCAN_IXR_SLP_MASK | XCAN_IXR_WKUP_MASK)) {
		priv->write_reg(priv, XCAN_ICR_OFFSET, (XCAN_IXR_SLP_MASK |
				XCAN_IXR_WKUP_MASK));
		xcan_state_interrupt(ndev, isr);
	}


	if (isr & XCAN_IXR_TXOK_MASK)
		xcan_tx_interrupt(ndev, isr);


	if (isr & (XCAN_IXR_ERROR_MASK | XCAN_IXR_RXOFLW_MASK |
			XCAN_IXR_BSOFF_MASK | XCAN_IXR_ARBLST_MASK)) {
		priv->write_reg(priv, XCAN_ICR_OFFSET, (XCAN_IXR_ERROR_MASK |
				XCAN_IXR_RXOFLW_MASK | XCAN_IXR_BSOFF_MASK |
				XCAN_IXR_ARBLST_MASK));
		xcan_err_interrupt(ndev, isr);
	}


	if (isr & (XCAN_IXR_RXNEMP_MASK | XCAN_IXR_RXOK_MASK)) {
		ier = priv->read_reg(priv, XCAN_IER_OFFSET);
		ier &= ~(XCAN_IXR_RXNEMP_MASK | XCAN_IXR_RXOK_MASK);
		priv->write_reg(priv, XCAN_IER_OFFSET, ier);
		napi_schedule(&priv->napi);
	}
	return IRQ_HANDLED;
}
