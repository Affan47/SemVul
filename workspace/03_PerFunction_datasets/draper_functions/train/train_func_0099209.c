sxgbe_common_interrupt(int irq, void *dev_id)
{
	struct net_device *netdev = (struct net_device *)dev_id;
	struct sxgbe_priv_data *priv = netdev_priv(netdev);
	int status;

	status = priv->hw->mac->host_irq_status(priv->ioaddr, &priv->xstats);

	if (status & TX_ENTRY_LPI_MODE) {
		priv->xstats.tx_lpi_entry_n++;
		priv->tx_path_in_lpi_mode = true;
	}
	if (status & TX_EXIT_LPI_MODE) {
		priv->xstats.tx_lpi_exit_n++;
		priv->tx_path_in_lpi_mode = false;
	}
	if (status & RX_ENTRY_LPI_MODE)
		priv->xstats.rx_lpi_entry_n++;
	if (status & RX_EXIT_LPI_MODE)
		priv->xstats.rx_lpi_exit_n++;

	return IRQ_HANDLED;
}
