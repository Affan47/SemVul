bond_3ad_set_carrier(struct bonding *bond)
{
	struct aggregator *active;
	struct slave *first_slave;
	int ret = 1;

	rcu_read_lock();
	first_slave = bond_first_slave_rcu(bond);
	if (!first_slave) {
		ret = 0;
		goto out;
	}
	active = __get_active_agg(&(SLAVE_AD_INFO(first_slave)->aggregator));
	if (active) {

		if (__agg_active_ports(active) < bond->params.min_links) {
			if (netif_carrier_ok(bond->dev)) {
				netif_carrier_off(bond->dev);
				goto out;
			}
		} else if (!netif_carrier_ok(bond->dev)) {
			netif_carrier_on(bond->dev);
			goto out;
		}
	} else if (netif_carrier_ok(bond->dev)) {
		netif_carrier_off(bond->dev);
	}
out:
	rcu_read_unlock();
	return ret;
}
