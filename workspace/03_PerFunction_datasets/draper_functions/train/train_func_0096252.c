net_con_clear_timeout(struct net_connection* con)
{
	if (con->timeout && timeout_evt_is_scheduled(con->timeout))
	{
		timeout_queue_remove(net_backend_get_timeout_queue(), con->timeout);
		hub_free(con->timeout);
		con->timeout = 0;
	}
}
