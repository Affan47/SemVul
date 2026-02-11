cf_exit(struct arasan_cf_dev *acdev)
{
	unsigned long flags;

	spin_lock_irqsave(&acdev->host->lock, flags);
	cf_ginterrupt_enable(acdev, 0);
	cf_interrupt_enable(acdev, TRUE_IDE_IRQS, 0);
	cf_card_reset(acdev);
	writel(readl(acdev->vbase + OP_MODE) & ~CFHOST_ENB,
			acdev->vbase + OP_MODE);
	spin_unlock_irqrestore(&acdev->host->lock, flags);
	clk_disable_unprepare(acdev->clk);
}
