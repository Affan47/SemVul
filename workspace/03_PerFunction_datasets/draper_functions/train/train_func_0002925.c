lb_port_enter(struct team *team, struct team_port *port)
{
	struct lb_port_priv *lb_port_priv = get_lb_port_priv(port);

	lb_port_priv->pcpu_stats = alloc_percpu(struct lb_stats);
	if (!lb_port_priv->pcpu_stats)
		return -ENOMEM;
	return 0;
}
