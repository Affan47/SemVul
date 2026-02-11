__reconstruct_port_hlist(struct team *team, int rm_index)
{
	int i;
	struct team_port *port;

	for (i = rm_index + 1; i < team->en_port_count; i++) {
		port = team_get_port_by_index(team, i);
		hlist_del_rcu(&port->hlist);
		port->index--;
		hlist_add_head_rcu(&port->hlist,
				   team_port_index_hash(team, port->index));
	}
}
