bonding_show_ad_actor_key(struct device *d,
					 struct device_attribute *attr,
					 char *buf)
{
	int count = 0;
	struct bonding *bond = to_bond(d);

	if (BOND_MODE(bond) == BOND_MODE_8023AD && capable(CAP_NET_ADMIN)) {
		struct ad_info ad_info;
		count = sprintf(buf, "%d\n",
				bond_3ad_get_active_agg_info(bond, &ad_info)
				?  0 : ad_info.actor_key);
	}

	return count;
}
