alb_fasten_mac_swap(struct bonding *bond, struct slave *slave1,
				struct slave *slave2)
{
	int slaves_state_differ = (bond_slave_can_tx(slave1) != bond_slave_can_tx(slave2));
	struct slave *disabled_slave = NULL;

	ASSERT_RTNL();


	if (bond_slave_can_tx(slave1)) {
		alb_send_learning_packets(slave1, slave1->dev->dev_addr, false);
		if (bond->alb_info.rlb_enabled) {


			rlb_req_update_slave_clients(bond, slave1);
		}
	} else {
		disabled_slave = slave1;
	}

	if (bond_slave_can_tx(slave2)) {
		alb_send_learning_packets(slave2, slave2->dev->dev_addr, false);
		if (bond->alb_info.rlb_enabled) {


			rlb_req_update_slave_clients(bond, slave2);
		}
	} else {
		disabled_slave = slave2;
	}

	if (bond->alb_info.rlb_enabled && slaves_state_differ) {

		rlb_teach_disabled_mac_on_primary(bond,
						  disabled_slave->dev->dev_addr);
	}
}
