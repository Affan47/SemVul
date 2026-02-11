dhcpnak (packet)
	struct packet *packet;
{
	struct interface_info *ip = packet -> interface;
	struct client_state *client;


	for (client = ip -> client; client; client = client -> next)
		if (client -> xid == packet -> raw -> xid)
			break;


	if (!client ||
	    (packet -> interface -> hw_address.hlen - 1 !=
	     packet -> raw -> hlen) ||
	    (memcmp (&packet -> interface -> hw_address.hbuf [1],
		     packet -> raw -> chaddr, packet -> raw -> hlen))) {
#if defined (DEBUG)
		log_debug ("DHCPNAK in wrong transaction.");
#endif
		return;
	}

	if (client -> state != S_REBOOTING &&
	    client -> state != S_REQUESTING &&
	    client -> state != S_RENEWING &&
	    client -> state != S_REBINDING) {
#if defined (DEBUG)
		log_debug ("DHCPNAK in wrong state.");
#endif
		return;
	}

	log_info ("DHCPNAK from %s (xid=0x%x)", piaddr (packet -> client_addr), client -> xid);

	if (!client -> active) {
#if defined (DEBUG)
		log_info ("DHCPNAK with no active lease.\n");
#endif
		return;
	}


	script_init(client, "EXPIRE", NULL);
	script_write_params(client, "old_", client->active);
	if (client->alias)
		script_write_params(client, "alias_", client->alias);
	script_go(client);

	destroy_client_lease (client -> active);
	client -> active = (struct client_lease *)0;


	cancel_timeout (send_request, client);


	script_init(client, "PREINIT", NULL);
	if (client->alias)
		script_write_params(client, "alias_", client->alias);
	script_go(client);

	client -> state = S_INIT;
	state_init (client);
}
