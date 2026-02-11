mvs_is_phy_ready(struct mvs_info *mvi, int i)
{
	u32 tmp;
	struct mvs_phy *phy = &mvi->phy[i];
	struct mvs_port *port = phy->port;

	tmp = MVS_CHIP_DISP->read_phy_ctl(mvi, i);
	if ((tmp & PHY_READY_MASK) && !(phy->irq_status & PHYEV_POOF)) {
		if (!port)
			phy->phy_attached = 1;
		return tmp;
	}

	if (port) {
		if (phy->phy_type & PORT_TYPE_SAS) {
			port->wide_port_phymap &= ~(1U << i);
			if (!port->wide_port_phymap)
				port->port_attached = 0;
			mvs_update_wideport(mvi, i);
		} else if (phy->phy_type & PORT_TYPE_SATA)
			port->port_attached = 0;
		phy->port = NULL;
		phy->phy_attached = 0;
		phy->phy_type &= ~(PORT_TYPE_SAS | PORT_TYPE_SATA);
	}
	return 0;
}
