amd8111e_init_ring(struct net_device *dev)
{
	struct amd8111e_priv *lp = netdev_priv(dev);
	int i;

	lp->rx_idx = lp->tx_idx = 0;
	lp->tx_complete_idx = 0;
	lp->tx_ring_idx = 0;


	if(lp->opened)

		amd8111e_free_skbs(dev);

	else{

	     	if((lp->tx_ring = pci_alloc_consistent(lp->pci_dev,
			sizeof(struct amd8111e_tx_dr)*NUM_TX_RING_DR,
			&lp->tx_ring_dma_addr)) == NULL)

			goto err_no_mem;

	     	if((lp->rx_ring = pci_alloc_consistent(lp->pci_dev,
			sizeof(struct amd8111e_rx_dr)*NUM_RX_RING_DR,
			&lp->rx_ring_dma_addr)) == NULL)

			goto err_free_tx_ring;

	}

	amd8111e_set_rx_buff_len(dev);


	for (i = 0; i < NUM_RX_BUFFERS; i++) {

		lp->rx_skbuff[i] = netdev_alloc_skb(dev, lp->rx_buff_len);
		if (!lp->rx_skbuff[i]) {

				for(--i; i >= 0 ;i--)
					dev_kfree_skb(lp->rx_skbuff[i]);
				goto err_free_rx_ring;
		}
		skb_reserve(lp->rx_skbuff[i],2);
	}

	for (i = 0; i < NUM_RX_BUFFERS; i++) {
		lp->rx_dma_addr[i] = pci_map_single(lp->pci_dev,
			lp->rx_skbuff[i]->data,lp->rx_buff_len-2, PCI_DMA_FROMDEVICE);

		lp->rx_ring[i].buff_phy_addr = cpu_to_le32(lp->rx_dma_addr[i]);
		lp->rx_ring[i].buff_count = cpu_to_le16(lp->rx_buff_len-2);
		wmb();
		lp->rx_ring[i].rx_flags = cpu_to_le16(OWN_BIT);
	}


	for (i = 0; i < NUM_TX_RING_DR; i++) {
		lp->tx_ring[i].buff_phy_addr = 0;
		lp->tx_ring[i].tx_flags = 0;
		lp->tx_ring[i].buff_count = 0;
	}

	return 0;

err_free_rx_ring:

	pci_free_consistent(lp->pci_dev,
		sizeof(struct amd8111e_rx_dr)*NUM_RX_RING_DR,lp->rx_ring,
		lp->rx_ring_dma_addr);

err_free_tx_ring:

	pci_free_consistent(lp->pci_dev,
		 sizeof(struct amd8111e_tx_dr)*NUM_TX_RING_DR,lp->tx_ring,
		 lp->tx_ring_dma_addr);

err_no_mem:
	return -ENOMEM;
}
