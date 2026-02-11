handleUdpPacket() {
	int r, srcnode, dlen;
	int srcroute;
	char ipversion;
	struct in_addr srcaddr4;
	struct in6_addr srcaddr6;

	if(!UDP_HASDATA()) return 0;
	logmsg(LOGGER_DEBUG, "Received UDP packet");

	if(UDP_RECVLEN < DPACK_MINPACKLEN) {
		logmsg(LOGGER_NOTICE, "Received too short UDP packet");
		UDP_CLEARRECVBUF();
		return 1;
	}

	if(!DPACK_CHECKPTYPE(UDP_RECVBUF)) {
		logmsg(LOGGER_NOTICE, "Invalid packet type");
		UDP_CLEARRECVBUF();
		return 1;
	}

	srcnode = DPACK_GETSRCNODE(UDP_RECVBUF);
	if(!NODEINFO_EXISTS(srcnode)) {
		logmsg(LOGGER_NOTICE, "Received packet from invalid node");
		UDP_CLEARRECVBUF();
		return 1;
	}


	if(!NODEINFO_INFO(srcnode).negotiated) {
		UDP_CLEARRECVBUF();
		logmsg(LOGGER_INFO, "Starting negotiation with %d", srcnode);
		r = tcpcon_newnegotiate(srcnode);
		if(r != TCPCON_OK) {
			logmsg(LOGGER_ERR, "Error starting negotiation");
			return 1;
		}
		return 0;
	}

	dlen = SENDRECVBUFSIZE;
	r = unpackageDataFromNetwork(UDP_RECVBUF, UDP_RECVLEN, TUN_SENDBUF, &dlen);
	if(r != 0) {
		logmsg(LOGGER_ERR, "Error unpacking data");
		UDP_CLEARRECVBUF();
		return 1;
	}
	TUN_SENDLEN = dlen;

	UDP_CLEARRECVBUF();

	logmsg(LOGGER_DEBUG, "Checking for spoofed source address");
	if(TUN_SENDLEN < IPPACKET_MINLEN) {
		logmsg(LOGGER_ERR, "Packet too short");
		return 1;
	}
	ipversion = IPPACKET_VERSION(TUN_SENDBUF);
	if(ipversion == 4) {
		if(TUN_SENDLEN < sizeof(struct ip)) {
			logmsg(LOGGER_ERR, "Packet too short");
			return 1;
		}
		srcaddr4 = IP4PACKET_SRCADDR(TUN_SENDBUF);
		r = routetable_getroute(&ipv4routetable, &srcaddr4, 32, &srcroute);
		if(r == ROUTETABLE_NOROUTE) {
			logmsg(LOGGER_WARNING, "Received packet from unroutable source address");
			return 1;
		}
		if(r != ROUTETABLE_OK) {
			logmsg(LOGGER_ERR, "Error looking up route");
			return 1;
		}
		if(srcroute != srcnode) {
			logmsg(LOGGER_ERR, "Received packet from spoofed source address.  Packet from node %d with source address routable to node %d.", srcnode, srcroute);
			return 1;
		}
	} else if(ipversion == 6) {
		if(TUN_SENDLEN < sizeof(struct ip6_hdr)) {
			logmsg(LOGGER_ERR, "Packet too short");
			return 1;
		}
		srcaddr6 = IP6PACKET_SRCADDR(TUN_SENDBUF);
		r = routetable_getroute(&ipv6routetable, &srcaddr6, 128, &srcroute);
		if(r == ROUTETABLE_NOROUTE) {
			logmsg(LOGGER_WARNING, "Received packet from unroutable source address");
			return 1;
		}
		if(r != ROUTETABLE_OK) {
			logmsg(LOGGER_ERR, "Error looking up route");
			return 1;
		}
		if(srcroute != srcnode) {
			logmsg(LOGGER_ERR, "Received packet from spoofed source address.  Packet from node %d with source address routable to node %d.", srcnode, srcroute);
			return 1;
		}
	} else {
		logmsg(LOGGER_ERR, "Invalid IP version");
		return 1;
	}
	return 0;
}
