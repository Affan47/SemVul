xcan_tx_interrupt(struct net_device *ndev, u32 isr)
{
	struct xcan_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;

	while ((priv->tx_head - priv->tx_tail > 0) &&
			(isr & XCAN_IXR_TXOK_MASK)) {
		priv->write_reg(priv, XCAN_ICR_OFFSET, XCAN_IXR_TXOK_MASK);
		can_get_echo_skb(ndev, priv->tx_tail %
					priv->tx_max);
		priv->tx_tail++;
		stats->tx_packets++;
		isr = priv->read_reg(priv, XCAN_ISR_OFFSET);
	}
	can_led_event(ndev, CAN_LED_EVENT_TX);
	netif_wake_queue(ndev);
}
