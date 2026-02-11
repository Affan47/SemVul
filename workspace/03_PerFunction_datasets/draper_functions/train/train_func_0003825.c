drbd_wait_for_connect(struct drbd_connection *connection, struct accept_wait_data *ad)
{
	int timeo, connect_int, err = 0;
	struct socket *s_estab = NULL;
	struct net_conf *nc;

	rcu_read_lock();
	nc = rcu_dereference(connection->net_conf);
	if (!nc) {
		rcu_read_unlock();
		return NULL;
	}
	connect_int = nc->connect_int;
	rcu_read_unlock();

	timeo = connect_int * HZ;

	timeo += (prandom_u32() & 1) ? timeo / 7 : -timeo / 7;

	err = wait_for_completion_interruptible_timeout(&ad->door_bell, timeo);
	if (err <= 0)
		return NULL;

	err = kernel_accept(ad->s_listen, &s_estab, 0);
	if (err < 0) {
		if (err != -EAGAIN && err != -EINTR && err != -ERESTARTSYS) {
			drbd_err(connection, "accept failed, err = %d\n", err);
			conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_HARD);
		}
	}

	if (s_estab)
		unregister_state_change(s_estab->sk, ad);

	return s_estab;
}
