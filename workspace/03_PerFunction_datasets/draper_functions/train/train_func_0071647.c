find_tx_buff(struct atmel_private *priv, u16 len)
{
	u16 bottom_free = priv->host_info.tx_buff_size - priv->tx_buff_tail;

	if (priv->tx_desc_free == 3 || priv->tx_free_mem < len)
		return 0;

	if (bottom_free >= len)
		return priv->host_info.tx_buff_pos + priv->tx_buff_tail;

	if (priv->tx_free_mem - bottom_free >= len) {
		priv->tx_buff_tail = 0;
		return priv->host_info.tx_buff_pos;
	}

	return 0;
}
