skge_down(struct net_device *dev)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	int port = skge->port;

	if (skge->mem == NULL)
		return 0;

	netif_info(skge, ifdown, skge->netdev, "disabling interface\n");

	netif_tx_disable(dev);

	if (is_genesis(hw) && hw->phy_type == SK_PHY_XMAC)
		del_timer_sync(&skge->link_timer);

	napi_disable(&skge->napi);
	netif_carrier_off(dev);

	spin_lock_irq(&hw->hw_lock);
	hw->intr_mask &= ~portmask[port];
	skge_write32(hw, B0_IMSK, (hw->ports == 1) ? 0 : hw->intr_mask);
	skge_read32(hw, B0_IMSK);
	spin_unlock_irq(&hw->hw_lock);

	if (hw->ports == 1)
		free_irq(hw->pdev->irq, hw);

	skge_write8(skge->hw, SK_REG(skge->port, LNK_LED_REG), LED_OFF);
	if (is_genesis(hw))
		genesis_stop(skge);
	else
		yukon_stop(skge);


	skge_write8(hw, Q_ADDR(txqaddr[port], Q_CSR), CSR_STOP);
	skge_write32(hw, RB_ADDR(txqaddr[port], RB_CTRL),
		     RB_RST_SET|RB_DIS_OP_MD);


	skge_write8(hw, SK_REG(port, TXA_CTRL),
		    TXA_DIS_FSYNC | TXA_DIS_ALLOC | TXA_STOP_RC);


	skge_write32(hw, SK_REG(port, TXA_ITI_INI), 0L);
	skge_write32(hw, SK_REG(port, TXA_LIM_INI), 0L);


	skge_write32(hw, Q_ADDR(txqaddr[port], Q_CSR), CSR_SET_RESET);
	skge_write32(hw, RB_ADDR(txqaddr[port], RB_CTRL), RB_RST_SET);


	skge_write8(hw, RB_ADDR(port == 0 ? Q_XA1 : Q_XA2, RB_CTRL), RB_RST_SET);

	skge_rx_stop(hw, port);

	if (is_genesis(hw)) {
		skge_write8(hw, SK_REG(port, TX_MFF_CTRL2), MFF_RST_SET);
		skge_write8(hw, SK_REG(port, RX_MFF_CTRL2), MFF_RST_SET);
	} else {
		skge_write8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_RST_SET);
		skge_write8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_RST_SET);
	}

	skge_led(skge, LED_MODE_OFF);

	netif_tx_lock_bh(dev);
	skge_tx_clean(dev);
	netif_tx_unlock_bh(dev);

	skge_rx_clean(skge);

	kfree(skge->rx_ring.start);
	kfree(skge->tx_ring.start);
	pci_free_consistent(hw->pdev, skge->mem_size, skge->mem, skge->dma);
	skge->mem = NULL;
	return 0;
}
