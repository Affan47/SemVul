__geneve_sock_release(struct geneve_sock *gs)
{
	if (!gs || --gs->refcnt)
		return;

	list_del(&gs->list);
	geneve_notify_del_rx_port(gs);
	udp_tunnel_sock_release(gs->sock);
	kfree_rcu(gs, rcu);
}
