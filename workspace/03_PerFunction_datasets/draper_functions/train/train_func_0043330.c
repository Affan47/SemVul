dhcpv6(struct packet *packet) {
	struct data_string reply;
	struct sockaddr_in6 to_addr;
	int send_ret;


	log_packet_in(packet);


	build_dhcpv6_reply(&reply, packet);

	if (reply.data != NULL) {


		memset(&to_addr, 0, sizeof(to_addr));
		to_addr.sin6_family = AF_INET6;
		if ((packet->dhcpv6_msg_type == DHCPV6_RELAY_FORW) ||
		    (packet->dhcpv6_msg_type == DHCPV6_RELAY_REPL)) {
			to_addr.sin6_port = local_port;
		} else {
			to_addr.sin6_port = remote_port;
		}

#if defined (REPLY_TO_SOURCE_PORT)


		to_addr.sin6_port = packet->client_port;
#endif

		memcpy(&to_addr.sin6_addr, packet->client_addr.iabuf,
		       sizeof(to_addr.sin6_addr));

		log_info("Sending %s to %s port %d",
			 dhcpv6_type_names[reply.data[0]],
			 piaddr(packet->client_addr),
			 ntohs(to_addr.sin6_port));

		send_ret = send_packet6(packet->interface,
					reply.data, reply.len, &to_addr);
		if (send_ret != reply.len) {
			log_error("dhcpv6: send_packet6() sent %d of %d bytes",
				  send_ret, reply.len);
		}
		data_string_forget(&reply, MDL);
	}
}
