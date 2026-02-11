acpi_pm_check_blacklist(struct pci_dev *dev)
{
	if (acpi_pm_good)
		return;


	if (dev->revision < 3) {
		printk(KERN_WARNING "* Found PM-Timer Bug on the chipset."
		       " Due to workarounds for a bug,\n"
		       "* this clock source is slow. Consider trying"
		       " other clock sources\n");

		acpi_pm_need_workaround();
	}
}
