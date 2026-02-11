sci_port_set_phy(struct isci_port *iport, struct isci_phy *iphy)
{


	if (!iport->phy_table[iphy->phy_index] &&
	    !phy_get_non_dummy_port(iphy) &&
	    sci_port_is_valid_phy_assignment(iport, iphy->phy_index)) {


		iport->logical_port_index = iport->physical_port_index;
		iport->phy_table[iphy->phy_index] = iphy;
		sci_phy_set_port(iphy, iport);

		return SCI_SUCCESS;
	}

	return SCI_FAILURE;
}
