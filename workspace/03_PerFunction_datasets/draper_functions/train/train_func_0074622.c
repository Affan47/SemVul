listen_port_changed(property_t prop)
{
	static uint32 old_port = (uint32) -1;


	if (
		GNET_PROPERTY(listen_port) == old_port &&
		GNET_PROPERTY(listen_port) > 1
	)
		return FALSE;

	if (old_port != (uint32) -1) {
		upnp_unmap_tcp(old_port);
		upnp_unmap_udp(old_port);
	}

	old_port = GNET_PROPERTY(listen_port);


	if (1 != GNET_PROPERTY(listen_port)) {
		request_new_sockets(GNET_PROPERTY(listen_port), FALSE);
	} else {
		bit_array_t tried[BIT_ARRAY_SIZE(65536)];
		uint num_tried = 0;
		uint32 port = GNET_PROPERTY(listen_port);


		bit_array_init(tried, 65536);
		bit_array_set_range(tried, 0, 1023);
		bit_array_clear_range(tried, 1024, 65535);

		do {
			uint32 i;

			i = random_value(65535 - 1024) + 1024;
			port = i;


			do {
				if (!bit_array_get(tried, i)) {
					port = i;
					break;
				}
				i = (i + 101) & 0xffff;
			} while (i != port);

			g_assert(port > 1023);
			request_new_sockets(port, FALSE);

			if (s_tcp_listen || s_tcp_listen6)
				break;

		} while (++num_tried < 65535 - 1024);

		old_port = port;
		gnet_prop_set_guint32_val(prop, port);
	}


	if (s_tcp_listen != NULL)
		upnp_map_tcp(old_port);

	if (s_udp_listen != NULL)
			upnp_map_udp(old_port);

	if (!settings_init_running) {
		inet_firewalled();
		inet_udp_firewalled(TRUE);
		inet_udp_check_unsolicited();
	}


    if (s_tcp_listen == NULL && GNET_PROPERTY(listen_port) != 0) {
		gcu_statusbar_warning(_("Failed to create listening sockets"));
		old_port = (uint32) -1;
        return TRUE;
    } else {
		old_port = GNET_PROPERTY(listen_port);
		remember_local_addr_port();
	}

    return FALSE;
}
