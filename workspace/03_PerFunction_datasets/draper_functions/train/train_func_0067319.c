bond_change_active_slave(struct bonding *bond, struct slave *new_active)
{
	struct slave *old_active;

	ASSERT_RTNL();

	old_active = rtnl_dereference(bond->curr_active_slave);

	if (old_active == new_active)
		return;

	if (new_active) {
		new_active->last_link_up = jiffies;

		if (new_active->link == BOND_LINK_BACK) {
			if (bond_uses_primary(bond)) {
				netdev_info(bond->dev, "making interface %s the new active one %d ms earlier\n",
					    new_active->dev->name,
					    (bond->params.updelay - new_active->delay) * bond->params.miimon);
			}

			new_active->delay = 0;
			bond_set_slave_link_state(new_active, BOND_LINK_UP,
						  BOND_SLAVE_NOTIFY_NOW);

			if (BOND_MODE(bond) == BOND_MODE_8023AD)
				bond_3ad_handle_link_change(new_active, BOND_LINK_UP);

			if (bond_is_lb(bond))
				bond_alb_handle_link_change(bond, new_active, BOND_LINK_UP);
		} else {
			if (bond_uses_primary(bond)) {
				netdev_info(bond->dev, "making interface %s the new active one\n",
					    new_active->dev->name);
			}
		}
	}

	if (bond_uses_primary(bond))
		bond_hw_addr_swap(bond, new_active, old_active);

	if (bond_is_lb(bond)) {
		bond_alb_handle_active_change(bond, new_active);
		if (old_active)
			bond_set_slave_inactive_flags(old_active,
						      BOND_SLAVE_NOTIFY_NOW);
		if (new_active)
			bond_set_slave_active_flags(new_active,
						    BOND_SLAVE_NOTIFY_NOW);
	} else {
		rcu_assign_pointer(bond->curr_active_slave, new_active);
	}

	if (BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP) {
		if (old_active)
			bond_set_slave_inactive_flags(old_active,
						      BOND_SLAVE_NOTIFY_NOW);

		if (new_active) {
			bool should_notify_peers = false;

			bond_set_slave_active_flags(new_active,
						    BOND_SLAVE_NOTIFY_NOW);

			if (bond->params.fail_over_mac)
				bond_do_fail_over_mac(bond, new_active,
						      old_active);

			if (netif_running(bond->dev)) {
				bond->send_peer_notif =
					bond->params.num_peer_notif;
				should_notify_peers =
					bond_should_notify_peers(bond);
			}

			call_netdevice_notifiers(NETDEV_BONDING_FAILOVER, bond->dev);
			if (should_notify_peers)
				call_netdevice_notifiers(NETDEV_NOTIFY_PEERS,
							 bond->dev);
		}
	}


	if (netif_running(bond->dev) && (bond->params.resend_igmp > 0) &&
	    ((bond_uses_primary(bond) && new_active) ||
	     BOND_MODE(bond) == BOND_MODE_ROUNDROBIN)) {
		bond->igmp_retrans = bond->params.resend_igmp;
		queue_delayed_work(bond->wq, &bond->mcast_work, 1);
	}
}
