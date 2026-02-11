__get_agg_selection_mode(struct port *port)
{
	struct bonding *bond = __get_bond_by_port(port);

	if (bond == NULL)
		return BOND_AD_STABLE;

	return bond->params.ad_select;
}
