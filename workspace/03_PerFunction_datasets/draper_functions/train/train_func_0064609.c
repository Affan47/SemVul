ad_actor_oper_port_state_show(struct slave *slave, char *buf)
{
	const struct port *ad_port;

	if (BOND_MODE(slave->bond) == BOND_MODE_8023AD) {
		ad_port = &SLAVE_AD_INFO(slave)->port;
		if (ad_port->aggregator)
			return sprintf(buf, "%u\n",
				       ad_port->actor_oper_port_state);
	}

	return sprintf(buf, "N/A\n");
}
