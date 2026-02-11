brcmf_pcie_quick_check_isr_v1(int irq, void *arg)
{
	struct brcmf_pciedev_info *devinfo = (struct brcmf_pciedev_info *)arg;
	u32 status;

	status = 0;
	pci_read_config_dword(devinfo->pdev, BRCMF_PCIE_REG_INTSTATUS, &status);
	if (status) {
		brcmf_pcie_intr_disable(devinfo);
		brcmf_dbg(PCIE, "Enter\n");
		return IRQ_WAKE_THREAD;
	}
	return IRQ_NONE;
}
