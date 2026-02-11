csio_nondata_isr(int irq, void *dev_id)
{
	struct csio_hw *hw = (struct csio_hw *) dev_id;
	int rv;
	unsigned long flags;

	if (unlikely(!hw))
		return IRQ_NONE;

	if (unlikely(pci_channel_offline(hw->pdev))) {
		CSIO_INC_STATS(hw, n_pcich_offline);
		return IRQ_NONE;
	}

	spin_lock_irqsave(&hw->lock, flags);
	csio_hw_slow_intr_handler(hw);
	rv = csio_mb_isr_handler(hw);

	if (rv == 0 && !(hw->flags & CSIO_HWF_FWEVT_PENDING)) {
		hw->flags |= CSIO_HWF_FWEVT_PENDING;
		spin_unlock_irqrestore(&hw->lock, flags);
		schedule_work(&hw->evtq_work);
		return IRQ_HANDLED;
	}
	spin_unlock_irqrestore(&hw->lock, flags);
	return IRQ_HANDLED;
}
