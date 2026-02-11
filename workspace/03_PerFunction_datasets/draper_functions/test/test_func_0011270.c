init(QJDns::Mode _mode, const QHostAddress &address)
	{
		mode = _mode;

		jdns_callbacks_t callbacks;
		callbacks.app = this;
		callbacks.time_now = cb_time_now;
		callbacks.rand_int = cb_rand_int;
		callbacks.debug_line = cb_debug_line;
		callbacks.udp_bind = cb_udp_bind;
		callbacks.udp_unbind = cb_udp_unbind;
		callbacks.udp_read = cb_udp_read;
		callbacks.udp_write = cb_udp_write;
		sess = jdns_session_new(&callbacks);
		jdns_set_hold_ids_enabled(sess, 1);
		next_handle = 1;
		need_handle = false;

		int ret;

		jdns_address_t *baddr = qt2addr(address);
		if(mode == Unicast)
		{
			ret = jdns_init_unicast(sess, baddr, 0);
		}
		else
		{
			jdns_address_t *maddr;
			if(address.protocol() == QAbstractSocket::IPv6Protocol)
				maddr = jdns_address_multicast6_new();
			else
				maddr = jdns_address_multicast4_new();
			ret = jdns_init_multicast(sess, baddr, JDNS_MULTICAST_PORT, maddr);
			jdns_address_delete(maddr);
		}
		jdns_address_delete(baddr);

		if(!ret)
		{
			jdns_session_delete(sess);
			sess = 0;
			return false;
		}
		return true;
	}
