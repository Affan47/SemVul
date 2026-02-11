pch_can_resume(struct pci_dev *pdev)
{
	int i;
	int retval;
	struct net_device *dev = pci_get_drvdata(pdev);
	struct pch_can_priv *priv = netdev_priv(dev);

	pci_set_power_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	retval = pci_enable_device(pdev);
	if (retval) {
		dev_err(&pdev->dev, "pci_enable_device failed.\n");
		return retval;
	}

	pci_enable_wake(pdev, PCI_D3hot, 0);

	priv->can.state = CAN_STATE_ERROR_ACTIVE;


	pch_can_set_int_enables(priv, PCH_CAN_DISABLE);


	pch_can_set_run_mode(priv, PCH_CAN_STOP);


	pch_can_config_rx_tx_buffers(priv);


	pch_set_bittiming(dev);


	pch_can_set_optmode(priv);


	for (i = PCH_TX_OBJ_START; i <= PCH_TX_OBJ_END; i++)
		pch_can_set_rxtx(priv, i, priv->tx_enable[i - 1], PCH_TX_IFREG);


	for (i = PCH_RX_OBJ_START; i <= PCH_RX_OBJ_END; i++) {

		pch_can_set_rx_buffer_link(priv, i, priv->rx_link[i - 1]);


		pch_can_set_rxtx(priv, i, priv->rx_enable[i - 1], PCH_RX_IFREG);
	}


	pch_can_set_int_custom(priv);


	pch_can_set_run_mode(priv, PCH_CAN_RUN);

	return retval;
}
