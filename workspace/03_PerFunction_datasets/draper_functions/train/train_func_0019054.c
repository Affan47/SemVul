rocker_port_bridge_ageing_time(struct rocker_port *rocker_port,
					  struct switchdev_trans *trans,
					  u32 ageing_time)
{
	struct rocker *rocker = rocker_port->rocker;

	if (!switchdev_trans_ph_prepare(trans)) {
		rocker_port->ageing_time = clock_t_to_jiffies(ageing_time);
		if (rocker_port->ageing_time < rocker->ageing_time)
			rocker->ageing_time = rocker_port->ageing_time;
		mod_timer(&rocker_port->rocker->fdb_cleanup_timer, jiffies);
	}

	return 0;
}
