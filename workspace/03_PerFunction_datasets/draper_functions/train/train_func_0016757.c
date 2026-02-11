bond_ethtool_get_settings(struct net_device *bond_dev,
				     struct ethtool_cmd *ecmd)
{
	struct bonding *bond = netdev_priv(bond_dev);
	unsigned long speed = 0;
	struct list_head *iter;
	struct slave *slave;

	ecmd->duplex = DUPLEX_UNKNOWN;
	ecmd->port = PORT_OTHER;


	bond_for_each_slave(bond, slave, iter) {
		if (bond_slave_can_tx(slave)) {
			if (slave->speed != SPEED_UNKNOWN)
				speed += slave->speed;
			if (ecmd->duplex == DUPLEX_UNKNOWN &&
			    slave->duplex != DUPLEX_UNKNOWN)
				ecmd->duplex = slave->duplex;
		}
	}
	ethtool_cmd_speed_set(ecmd, speed ? : SPEED_UNKNOWN);

	return 0;
}
