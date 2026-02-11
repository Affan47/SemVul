xhci_port_missing_cas_quirk(int port_index,
					     __le32 __iomem **port_array)
{
	u32 portsc;

	portsc = readl(port_array[port_index]);


	if (portsc & (PORT_CONNECT | PORT_CAS))
		return false;

	if (((portsc & PORT_PLS_MASK) != XDEV_POLLING) &&
	    ((portsc & PORT_PLS_MASK) != XDEV_COMP_MODE))
		return false;


	portsc &= ~(PORT_RWC_BITS | PORT_CEC | PORT_WAKE_BITS);
	portsc |= PORT_WR;
	writel(portsc, port_array[port_index]);

	readl(port_array[port_index]);
	return true;
}
