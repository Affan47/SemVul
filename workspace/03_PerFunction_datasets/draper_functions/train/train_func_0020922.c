got_packet (u_char * useless,
	    const struct pcap_pkthdr* hdr,
	    const u_char* packet)


{


	if(expired_flag == CHECK_GOTPACKET) {
		check_expired();
	}
	expired_flag = CHECK_NOT;

	if(! packet)
		fault( "got_packet", "didn't grab packet" );

	pcapheader = hdr;

	count_packets++;

	ippacket=(struct ip *)(packet + datalink_size);

#if __BYTE_ORDER == __LITTLE_ENDIAN
	iplen = (ippacket->ip_len % 256) * 256 + (ippacket->ip_len) / 256;
#elif __BYTE_ORDER == __BIG_ENDIAN
	iplen = ippacket->ip_len;
#else
# error "Please fix <bits/endian.h>"
#endif

	switch(ippacket->ip_p) {
	case IPPROTO_TCP:

		tcppacket = (struct tcphdr *)(packet + datalink_size + IP_SIZE);
		tcp_size = tcppacket->doff * 4;
		payload = (u_char *)(packet + datalink_size + IP_SIZE + tcp_size);
		payload_len = iplen - IP_SIZE - tcp_size;

#ifdef TCPICK_DEBUG
		if( payload_len != (hdr->len - (int)( payload - packet ) ) ) {
		    suicide( "got_packet",
			     "payload lenght calculated with iplen and hdr->len\n"
			     "differs by %d bytes\n"
			     "hdr->len = %d\n"
			     "datalink_size  = %d\n"
			     "IP_SIZE  = %d\n"
			     "iplen    = %d\n"
			     "tcp_size = %d\n"
			     "iplen - IP_SIZE - tcp_size = %d\n"
			     "(hdr->len - (int)( payload - packet ) = %d\n",
			     payload_len - (hdr->len - (int)( payload - packet )),
			     hdr->len,
			     datalink_size,
			     IP_SIZE,
			     iplen,
			     tcp_size,
			     payload_len,
			     (hdr->len - (int)( payload - packet ))
			    );
		}

#endif

		if( flags.header > 0 )
			display_header( stdout, ippacket, tcppacket,
					payload_len );

		verify();

		if( payload_len == 0 || SILENCE )
			goto end;

		out_flavour( flags.display_payload,
			     stdout, payload, payload_len );

		break;

 	case IPPROTO_UDP:
 		udppacket = (struct udphdr *)(packet + datalink_size + IP_SIZE);
 		payload = (u_char *)(packet + datalink_size + IP_SIZE + sizeof(*udppacket));
 		payload_len = hdr->len - (int)( payload - packet );

 		if( payload_len == 0 || SILENCE )
			goto end;

 		out_flavour( flags.display_payload,
 			     stdout, payload, payload_len );

 		break;


	default:
		debug( "Packet with unidentified protocol caught: %s > %s",
		       inet_ntoa(ippacket->ip_src),
		       inet_ntoa(ippacket->ip_dst) );
	}

end:

	if( flags.exitpackets != 0 ) {
		if (count_packets == flags.exitpackets)
			exit(EXIT_SUCCESS);
	}


	expired_flag = CHECK_LISTENING;
}
