bdx_rx_free(struct bdx_priv *priv)
{
	ENTER;
	if (priv->rxdb) {
		bdx_rx_free_skbs(priv, &priv->rxf_fifo0);
		bdx_rxdb_destroy(priv->rxdb);
		priv->rxdb = NULL;
	}
	bdx_fifo_free(priv, &priv->rxf_fifo0.m);
	bdx_fifo_free(priv, &priv->rxd_fifo0.m);

	RET();
}
