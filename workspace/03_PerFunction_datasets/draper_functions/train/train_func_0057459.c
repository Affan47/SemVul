lb_tx_hash_to_port_mapping_null_port(struct team *team,
						 struct team_port *port)
{
	struct lb_priv *lb_priv = get_lb_priv(team);
	bool changed = false;
	int i;

	for (i = 0; i < LB_TX_HASHTABLE_SIZE; i++) {
		struct lb_port_mapping *pm;

		pm = &lb_priv->ex->tx_hash_to_port_mapping[i];
		if (rcu_access_pointer(pm->port) == port) {
			RCU_INIT_POINTER(pm->port, NULL);
			team_option_inst_set_change(pm->opt_inst_info);
			changed = true;
		}
	}
	if (changed)
		team_options_change_check(team);
}
