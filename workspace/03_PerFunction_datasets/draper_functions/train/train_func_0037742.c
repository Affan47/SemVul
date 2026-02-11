sh_eth_ring_init(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	int rx_ringsize, tx_ringsize;


	mdp->rx_buf_sz = (ndev->mtu <= 1492 ? PKT_BUF_SZ :
			  (((ndev->mtu + 26 + 7) & ~7) + 2 + 16));
	if (mdp->cd->rpadir)
		mdp->rx_buf_sz += NET_IP_ALIGN;


	mdp->rx_skbuff = kcalloc(mdp->num_rx_ring, sizeof(*mdp->rx_skbuff),
				 GFP_KERNEL);
	if (!mdp->rx_skbuff)
		return -ENOMEM;

	mdp->tx_skbuff = kcalloc(mdp->num_tx_ring, sizeof(*mdp->tx_skbuff),
				 GFP_KERNEL);
	if (!mdp->tx_skbuff)
		goto ring_free;


	rx_ringsize = sizeof(struct sh_eth_rxdesc) * mdp->num_rx_ring;
	mdp->rx_ring = dma_alloc_coherent(NULL, rx_ringsize, &mdp->rx_desc_dma,
					  GFP_KERNEL);
	if (!mdp->rx_ring)
		goto ring_free;

	mdp->dirty_rx = 0;


	tx_ringsize = sizeof(struct sh_eth_txdesc) * mdp->num_tx_ring;
	mdp->tx_ring = dma_alloc_coherent(NULL, tx_ringsize, &mdp->tx_desc_dma,
					  GFP_KERNEL);
	if (!mdp->tx_ring)
		goto ring_free;
	return 0;

ring_free:

	sh_eth_ring_free(ndev);

	return -ENOMEM;
}
