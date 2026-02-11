xhci_print_ports(struct xhci_hcd *xhci)
{
	__le32 __iomem *addr;
	int i, j;
	int ports;
	char *names[NUM_PORT_REGS] = {
		"status",
		"power",
		"link",
		"reserved",
	};

	ports = HCS_MAX_PORTS(xhci->hcs_params1);
	addr = &xhci->op_regs->port_status_base;
	for (i = 0; i < ports; i++) {
		for (j = 0; j < NUM_PORT_REGS; ++j) {
			xhci_dbg(xhci, "%p port %s reg = 0x%x\n",
					addr, names[j],
					(unsigned int) readl(addr));
			addr++;
		}
	}
}
