nps_enet_irq_handler(s32 irq, void *dev_instance)
{
	struct net_device *ndev = dev_instance;
	struct nps_enet_priv *priv = netdev_priv(ndev);
	struct nps_enet_rx_ctl rx_ctrl;
	struct nps_enet_tx_ctl tx_ctrl;

	rx_ctrl.value = nps_enet_reg_get(priv, NPS_ENET_REG_RX_CTL);
	tx_ctrl.value = nps_enet_reg_get(priv, NPS_ENET_REG_TX_CTL);

	if ((!tx_ctrl.ct && priv->tx_packet_sent) || rx_ctrl.cr)
		if (likely(napi_schedule_prep(&priv->napi))) {
			nps_enet_reg_set(priv, NPS_ENET_REG_BUF_INT_ENABLE, 0);
			__napi_schedule(&priv->napi);
		}

	return IRQ_HANDLED;
}
