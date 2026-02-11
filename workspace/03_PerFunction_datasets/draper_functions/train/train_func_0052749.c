qlcnic_82xx_clear_legacy_intr(struct qlcnic_adapter *adapter)
{
	u32 status;

	status = readl(adapter->isr_int_vec);

	if (!(status & adapter->ahw->int_vec_bit))
		return IRQ_NONE;


	status = readl(adapter->crb_int_state_reg);
	if (!ISR_LEGACY_INT_TRIGGERED(status))
		return IRQ_NONE;

	writel(0xffffffff, adapter->tgt_status_reg);

	readl(adapter->isr_int_vec);
	readl(adapter->isr_int_vec);

	return IRQ_HANDLED;
}
