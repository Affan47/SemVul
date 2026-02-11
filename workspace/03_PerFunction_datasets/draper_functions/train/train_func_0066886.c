xcan_state_interrupt(struct net_device *ndev, u32 isr)
{
	struct xcan_priv *priv = netdev_priv(ndev);


	if (isr & XCAN_IXR_SLP_MASK)
		priv->can.state = CAN_STATE_SLEEPING;


	if (isr & XCAN_IXR_WKUP_MASK)
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
}
