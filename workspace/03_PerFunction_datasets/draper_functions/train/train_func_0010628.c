vlsi_start_clock(struct pci_dev *pdev)
{
	u8	clkctl, lock;
	int	i, count;

	if (clksrc < 2) {
		clkctl = CLKCTL_PD_INV | CLKCTL_CLKSTP;
		pci_write_config_byte(pdev, VLSI_PCI_CLKCTL, clkctl);


		udelay(500);
		count = 0;
		for (i = 500; i <= 10000; i += 50) {
			pci_read_config_byte(pdev, VLSI_PCI_CLKCTL, &lock);
			if (lock&CLKCTL_LOCK) {
				if (++count >= 3)
					break;
			}
			udelay(50);
		}
		if (count < 3) {
			if (clksrc == 1) {
				net_err_ratelimited("%s: no PLL or failed to lock!\n",
						    __func__);
				clkctl = CLKCTL_CLKSTP;
				pci_write_config_byte(pdev, VLSI_PCI_CLKCTL, clkctl);
				return -1;
			}
			else
				clksrc = 3;

			pr_debug("%s: PLL not locked, fallback to clksrc=%d\n",
				 __func__, clksrc);
		}
		else
			clksrc = 1;
	}

	if (clksrc != 1) {


		clkctl = CLKCTL_EXTCLK | CLKCTL_CLKSTP;
		if (clksrc == 3)
			clkctl |= CLKCTL_XCKSEL;
		pci_write_config_byte(pdev, VLSI_PCI_CLKCTL, clkctl);


	}
	else
		pci_read_config_byte(pdev, VLSI_PCI_CLKCTL, &clkctl);


	clkctl &= ~CLKCTL_CLKSTP;
	pci_write_config_byte(pdev, VLSI_PCI_CLKCTL, clkctl);

	return 0;
}
