xgene_enet_set_irq_name(struct net_device *ndev)
{
	struct xgene_enet_pdata *pdata = netdev_priv(ndev);
	struct xgene_enet_desc_ring *ring;
	int i;

	for (i = 0; i < pdata->rxq_cnt; i++) {
		ring = pdata->rx_ring[i];
		if (!pdata->cq_cnt) {
			snprintf(ring->irq_name, IRQ_ID_SIZE, "%s-rx-txc",
				 ndev->name);
		} else {
			snprintf(ring->irq_name, IRQ_ID_SIZE, "%s-rx-%d",
				 ndev->name, i);
		}
	}

	for (i = 0; i < pdata->cq_cnt; i++) {
		ring = pdata->tx_ring[i]->cp_ring;
		snprintf(ring->irq_name, IRQ_ID_SIZE, "%s-txc-%d",
			 ndev->name, i);
	}
}
