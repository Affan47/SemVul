bonding_show_ad_partner_mac(struct device *d,
					   struct device_attribute *attr,
					   char *buf)
{
	int count = 0;
	struct bonding *bond = to_bond(d);

	if (BOND_MODE(bond) == BOND_MODE_8023AD && capable(CAP_NET_ADMIN)) {
		struct ad_info ad_info;
		if (!bond_3ad_get_active_agg_info(bond, &ad_info))
			count = sprintf(buf, "%pM\n", ad_info.partner_system);
	}

	return count;
}
