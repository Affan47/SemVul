ipr_test_msi(struct ipr_ioa_cfg *ioa_cfg, struct pci_dev *pdev)
{
	int rc;
	volatile u32 int_reg;
	unsigned long lock_flags = 0;

	ENTER;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	init_waitqueue_head(&ioa_cfg->msi_wait_q);
	ioa_cfg->msi_received = 0;
	ipr_mask_and_clear_interrupts(ioa_cfg, ~IPR_PCII_IOA_TRANS_TO_OPER);
	writel(IPR_PCII_IO_DEBUG_ACKNOWLEDGE, ioa_cfg->regs.clr_interrupt_mask_reg32);
	int_reg = readl(ioa_cfg->regs.sense_interrupt_mask_reg);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	if (ioa_cfg->intr_flag == IPR_USE_MSIX)
		rc = request_irq(ioa_cfg->vectors_info[0].vec, ipr_test_intr, 0, IPR_NAME, ioa_cfg);
	else
		rc = request_irq(pdev->irq, ipr_test_intr, 0, IPR_NAME, ioa_cfg);
	if (rc) {
		dev_err(&pdev->dev, "Can not assign irq %d\n", pdev->irq);
		return rc;
	} else if (ipr_debug)
		dev_info(&pdev->dev, "IRQ assigned: %d\n", pdev->irq);

	writel(IPR_PCII_IO_DEBUG_ACKNOWLEDGE, ioa_cfg->regs.sense_interrupt_reg32);
	int_reg = readl(ioa_cfg->regs.sense_interrupt_reg);
	wait_event_timeout(ioa_cfg->msi_wait_q, ioa_cfg->msi_received, HZ);
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	ipr_mask_and_clear_interrupts(ioa_cfg, ~IPR_PCII_IOA_TRANS_TO_OPER);

	if (!ioa_cfg->msi_received) {

		dev_info(&pdev->dev, "MSI test failed.  Falling back to LSI.\n");
		rc = -EOPNOTSUPP;
	} else if (ipr_debug)
		dev_info(&pdev->dev, "MSI test succeeded.\n");

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);

	if (ioa_cfg->intr_flag == IPR_USE_MSIX)
		free_irq(ioa_cfg->vectors_info[0].vec, ioa_cfg);
	else
		free_irq(pdev->irq, ioa_cfg);

	LEAVE;

	return rc;
}
