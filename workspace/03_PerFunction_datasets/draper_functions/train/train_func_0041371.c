bnxt_free_tx_rings(struct bnxt *bp)
{
	int i;
	struct pci_dev *pdev = bp->pdev;

	if (!bp->tx_ring)
		return;

	for (i = 0; i < bp->tx_nr_rings; i++) {
		struct bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		struct bnxt_ring_struct *ring;

		if (txr->tx_push) {
			dma_free_coherent(&pdev->dev, bp->tx_push_size,
					  txr->tx_push, txr->tx_push_mapping);
			txr->tx_push = NULL;
		}

		ring = &txr->tx_ring_struct;

		bnxt_free_ring(bp, ring);
	}
}
