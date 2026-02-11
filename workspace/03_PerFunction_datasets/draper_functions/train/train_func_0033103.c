bnx2_setup_int_mode(struct bnx2 *bp, int dis_msi)
{
	int cpus = netif_get_num_default_rss_queues();
	int msix_vecs;

	if (!bp->num_req_rx_rings)
		msix_vecs = max(cpus + 1, bp->num_req_tx_rings);
	else if (!bp->num_req_tx_rings)
		msix_vecs = max(cpus, bp->num_req_rx_rings);
	else
		msix_vecs = max(bp->num_req_rx_rings, bp->num_req_tx_rings);

	msix_vecs = min(msix_vecs, RX_MAX_RINGS);

	bp->irq_tbl[0].handler = bnx2_interrupt;
	strcpy(bp->irq_tbl[0].name, bp->dev->name);
	bp->irq_nvecs = 1;
	bp->irq_tbl[0].vector = bp->pdev->irq;

	if ((bp->flags & BNX2_FLAG_MSIX_CAP) && !dis_msi)
		bnx2_enable_msix(bp, msix_vecs);

	if ((bp->flags & BNX2_FLAG_MSI_CAP) && !dis_msi &&
	    !(bp->flags & BNX2_FLAG_USING_MSIX)) {
		if (pci_enable_msi(bp->pdev) == 0) {
			bp->flags |= BNX2_FLAG_USING_MSI;
			if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
				bp->flags |= BNX2_FLAG_ONE_SHOT_MSI;
				bp->irq_tbl[0].handler = bnx2_msi_1shot;
			} else
				bp->irq_tbl[0].handler = bnx2_msi;

			bp->irq_tbl[0].vector = bp->pdev->irq;
		}
	}

	if (!bp->num_req_tx_rings)
		bp->num_tx_rings = rounddown_pow_of_two(bp->irq_nvecs);
	else
		bp->num_tx_rings = min(bp->irq_nvecs, bp->num_req_tx_rings);

	if (!bp->num_req_rx_rings)
		bp->num_rx_rings = bp->irq_nvecs;
	else
		bp->num_rx_rings = min(bp->irq_nvecs, bp->num_req_rx_rings);

	netif_set_real_num_tx_queues(bp->dev, bp->num_tx_rings);

	return netif_set_real_num_rx_queues(bp->dev, bp->num_rx_rings);
}
