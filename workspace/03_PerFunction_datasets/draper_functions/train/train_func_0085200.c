bnxt_init_inta(struct bnxt *bp)
{
	bp->irq_tbl = kcalloc(1, sizeof(struct bnxt_irq), GFP_KERNEL);
	if (!bp->irq_tbl)
		return -ENOMEM;

	bp->total_irqs = 1;
	bp->rx_nr_rings = 1;
	bp->tx_nr_rings = 1;
	bp->cp_nr_rings = 1;
	bp->tx_nr_rings_per_tc = bp->tx_nr_rings;
	bp->flags |= BNXT_FLAG_SHARED_RINGS;
	bp->irq_tbl[0].vector = bp->pdev->irq;
	return 0;
}
