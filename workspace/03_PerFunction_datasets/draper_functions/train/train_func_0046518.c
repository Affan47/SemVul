csio_fwevt_isr(int irq, void *dev_id)
{
	struct csio_hw *hw = (struct csio_hw *) dev_id;

	if (unlikely(!hw))
		return IRQ_NONE;

	if (unlikely(pci_channel_offline(hw->pdev))) {
		CSIO_INC_STATS(hw, n_pcich_offline);
		return IRQ_NONE;
	}

	csio_fwevt_handler(hw);

	return IRQ_HANDLED;
}
