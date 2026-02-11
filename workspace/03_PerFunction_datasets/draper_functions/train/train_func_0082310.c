islpci_mgt_cleanup_transmit(struct net_device *ndev)
{
	islpci_private *priv = netdev_priv(ndev);
	isl38xx_control_block *cb =
	    (isl38xx_control_block *) priv->control_block;
	u32 curr_frag;

#if VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_FUNCTION_CALLS, "islpci_mgt_cleanup_transmit\n");
#endif


	curr_frag = le32_to_cpu(cb->device_curr_frag[ISL38XX_CB_TX_MGMTQ]);
	barrier();

	for (; priv->index_mgmt_tx < curr_frag; priv->index_mgmt_tx++) {
		int index = priv->index_mgmt_tx % ISL38XX_CB_MGMT_QSIZE;
		struct islpci_membuf *buf = &priv->mgmt_tx[index];
		pci_unmap_single(priv->pdev, buf->pci_addr, buf->size,
				 PCI_DMA_TODEVICE);
		buf->pci_addr = 0;
		kfree(buf->mem);
		buf->mem = NULL;
		buf->size = 0;
	}
}
