arpspoof_test(struct arp_spoof_info *asi)
{
	struct timeval tv;
	struct timespec timeout;
	struct ifunc_item ifunc_pingtest;
	struct packet *p;
	int retval;
	int i;

	if (!asi->dst_mac_valid) {
		fprintf(stderr, "error: try to do arpspoof_test without known dst mac\n");
		return -1;
	}
	ifunc_pingtest.func = hunt_arpspoof_test;
	ifunc_pingtest.arg = asi;
	list_enqueue(&l_ifunc_icmp, &ifunc_pingtest);

	for (i = 0, retval = 0; i < 3 && !retval; i++) {
		send_icmp_request(asi->src_addr, asi->dst_addr, asi->src_fake_mac,
				  asi->dst_mac, 1 + i);
		gettimeofday(&tv, NULL);
		timeout.tv_sec = tv.tv_sec + 1;
		timeout.tv_nsec = tv.tv_usec * 1000;
		while ((p = list_consume(&l_arpspoof_test, &timeout))) {
			retval = is_icmp_reply(p, asi->dst_addr, asi->src_addr,
					       asi->dst_mac, asi->src_fake_mac);
			packet_free(p);
			if (retval)
				break;
		}
	}
	list_remove(&l_ifunc_icmp, &ifunc_pingtest);
	packet_flush(&l_arpspoof_test);

	if (retval == 1)
		return 0;
	else if (retval == 2)
		return -1;

	return -1;
}
