sci_port_configuration_agent_find_port(
	struct isci_host *ihost,
	struct isci_phy *iphy)
{
	u8 i;
	struct sci_sas_address port_sas_address;
	struct sci_sas_address port_attached_device_address;
	struct sci_sas_address phy_sas_address;
	struct sci_sas_address phy_attached_device_address;


	sci_phy_get_sas_address(iphy, &phy_sas_address);
	sci_phy_get_attached_sas_address(iphy, &phy_attached_device_address);

	for (i = 0; i < ihost->logical_port_entries; i++) {
		struct isci_port *iport = &ihost->ports[i];

		sci_port_get_sas_address(iport, &port_sas_address);
		sci_port_get_attached_sas_address(iport, &port_attached_device_address);

		if (sci_sas_address_compare(port_sas_address, phy_sas_address) == 0 &&
		    sci_sas_address_compare(port_attached_device_address, phy_attached_device_address) == 0)
			return iport;
	}

	return NULL;
}
