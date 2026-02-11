tco_timer_enable(void)
{
	int val;

	if (sp5100_tco_pci->revision >= 0x40) {


		outb(SB800_PM_WATCHDOG_CONFIG, SB800_IO_PM_INDEX_REG);
		val = inb(SB800_IO_PM_DATA_REG);
		val |= SB800_PM_WATCHDOG_SECOND_RES;
		outb(val, SB800_IO_PM_DATA_REG);


		outb(SB800_PM_WATCHDOG_CONTROL, SB800_IO_PM_INDEX_REG);
		val = inb(SB800_IO_PM_DATA_REG);
		val |= SB800_PCI_WATCHDOG_DECODE_EN;
		val &= ~SB800_PM_WATCHDOG_DISABLE;
		outb(val, SB800_IO_PM_DATA_REG);
	} else {


		pci_read_config_dword(sp5100_tco_pci,
				      SP5100_PCI_WATCHDOG_MISC_REG,
				      &val);

		val |= SP5100_PCI_WATCHDOG_DECODE_EN;

		pci_write_config_dword(sp5100_tco_pci,
				       SP5100_PCI_WATCHDOG_MISC_REG,
				       val);


		outb(SP5100_PM_WATCHDOG_CONTROL, SP5100_IO_PM_INDEX_REG);
		val = inb(SP5100_IO_PM_DATA_REG);
		val |= SP5100_PM_WATCHDOG_SECOND_RES;
		val &= ~SP5100_PM_WATCHDOG_DISABLE;
		outb(val, SP5100_IO_PM_DATA_REG);
	}
}
