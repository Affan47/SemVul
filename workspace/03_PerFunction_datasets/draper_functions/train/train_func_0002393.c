team_port_disable(struct team *team,
			      struct team_port *port)
{
	if (!team_port_enabled(port))
		return;
	if (team->ops.port_disabled)
		team->ops.port_disabled(team, port);
	hlist_del_rcu(&port->hlist);
	__reconstruct_port_hlist(team, port->index);
	port->index = -1;
	team->en_port_count--;
	team_queue_override_port_del(team, port);
	team_adjust_ops(team);
	team_notify_peers(team);
	team_mcast_rejoin(team);
}
