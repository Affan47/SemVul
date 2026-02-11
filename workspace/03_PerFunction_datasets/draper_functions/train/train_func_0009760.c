stmmac_enable_eee_mode(struct stmmac_priv *priv)
{

	if ((priv->dirty_tx == priv->cur_tx) &&
	    (priv->tx_path_in_lpi_mode == false))
		priv->hw->mac->set_eee_mode(priv->hw);
}
