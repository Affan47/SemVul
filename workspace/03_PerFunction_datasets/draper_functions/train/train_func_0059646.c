bond_option_ad_actor_system_set(struct bonding *bond,
					   const struct bond_opt_value *newval)
{
	u8 macaddr[ETH_ALEN];
	u8 *mac;
	int i;

	if (newval->string) {
		i = sscanf(newval->string, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
			   &macaddr[0], &macaddr[1], &macaddr[2],
			   &macaddr[3], &macaddr[4], &macaddr[5]);
		if (i != ETH_ALEN)
			goto err;
		mac = macaddr;
	} else {
		mac = (u8 *)&newval->value;
	}

	if (!is_valid_ether_addr(mac))
		goto err;

	netdev_info(bond->dev, "Setting ad_actor_system to %pM\n", mac);
	ether_addr_copy(bond->params.ad_actor_system, mac);
	return 0;

err:
	netdev_err(bond->dev, "Invalid MAC address.\n");
	return -EINVAL;
}
