nps_enet_clean_rx_fifo(struct net_device *ndev, u32 frame_len)
{
	struct nps_enet_priv *priv = netdev_priv(ndev);
	u32 i, len = DIV_ROUND_UP(frame_len, sizeof(u32));


	for (i = 0; i < len; i++)
		nps_enet_reg_get(priv, NPS_ENET_REG_RX_BUF);
}
