sky2_test_msi(struct sky2_hw *hw)
{
	struct pci_dev *pdev = hw->pdev;
	int err;

	init_waitqueue_head(&hw->msi_wait);

	err = request_irq(pdev->irq, sky2_test_intr, 0, DRV_NAME, hw);
	if (err) {
		dev_err(&pdev->dev, "cannot assign irq %d\n", pdev->irq);
		return err;
	}

	sky2_write32(hw, B0_IMSK, Y2_IS_IRQ_SW);

	sky2_write8(hw, B0_CTST, CS_ST_SW_IRQ);
	sky2_read8(hw, B0_CTST);

	wait_event_timeout(hw->msi_wait, (hw->flags & SKY2_HW_USE_MSI), HZ/10);

	if (!(hw->flags & SKY2_HW_USE_MSI)) {

		dev_info(&pdev->dev, "No interrupt generated using MSI, "
			 "switching to INTx mode.\n");

		err = -EOPNOTSUPP;
		sky2_write8(hw, B0_CTST, CS_CL_SW_IRQ);
	}

	sky2_write32(hw, B0_IMSK, 0);
	sky2_read32(hw, B0_IMSK);

	free_irq(pdev->irq, hw);

	return err;
}
