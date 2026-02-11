make_discover (client, lease)
	struct client_state *client;
	struct client_lease *lease;
{
	unsigned char discover = DHCPDISCOVER;
	struct option_state *options = (struct option_state *)0;

	memset (&client -> packet, 0, sizeof (client -> packet));

	make_client_options (client,
			     lease, &discover, (struct option_cache *)0,
			     lease ? &lease -> address : (struct iaddr *)0,
			     client -> config -> requested_options,
			     &options);


	client -> packet_length =
		cons_options ((struct packet *)0, &client -> packet,
			      (struct lease *)0, client,
			      1500,
			      (struct option_state *)0,
			      options,
			       &global_scope,
			       0,
			      0,
			      0,
			      (struct data_string *)0,
			      client -> config -> vendor_space_name);

	option_state_dereference (&options, MDL);
	if (client -> packet_length < BOOTP_MIN_LEN)
		client -> packet_length = BOOTP_MIN_LEN;

	client -> packet.op = BOOTREQUEST;
	client -> packet.htype = client -> interface -> hw_address.hbuf [0];
	client -> packet.hlen = client -> interface -> hw_address.hlen - 1;
	client -> packet.hops = 0;
	client -> packet.xid = random ();
	client -> packet.secs = 0;

	if (can_receive_unicast_unconfigured (client -> interface))
		client -> packet.flags = 0;
	else
		client -> packet.flags = htons (BOOTP_BROADCAST);

	memset (&(client -> packet.ciaddr),
		0, sizeof client -> packet.ciaddr);
	memset (&(client -> packet.yiaddr),
		0, sizeof client -> packet.yiaddr);
	memset (&(client -> packet.siaddr),
		0, sizeof client -> packet.siaddr);
	client -> packet.giaddr = giaddr;
	if (client -> interface -> hw_address.hlen > 0)
	    memcpy (client -> packet.chaddr,
		    &client -> interface -> hw_address.hbuf [1],
		    (unsigned)(client -> interface -> hw_address.hlen - 1));

#ifdef DEBUG_PACKET
	dump_raw ((unsigned char *)&client -> packet, client -> packet_length);
#endif
}
