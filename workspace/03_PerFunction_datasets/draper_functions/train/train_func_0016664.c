ath10k_pci_irq_pending(struct ath10k *ar)
{
	u32 cause;


	cause = ath10k_pci_read32(ar, SOC_CORE_BASE_ADDRESS +
				  PCIE_INTR_CAUSE_ADDRESS);
	if (cause & (PCIE_INTR_FIRMWARE_MASK | PCIE_INTR_CE_MASK_ALL))
		return true;

	return false;
}
