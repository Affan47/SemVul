stub_print_net_sock6_stats(struct activity *a, int curr, int dispavg)
{
	struct stats_net_sock6
		*snsc = (struct stats_net_sock6 *) a->buf[curr];
	static unsigned long long
		avg_tcp6_inuse  = 0,
		avg_udp6_inuse  = 0,
		avg_raw6_inuse  = 0,
		avg_frag6_inuse = 0;

	if (dis) {
		printf("\n%-11s   tcp6sck   udp6sck   raw6sck  ip6-frag\n",
		       timestamp[!curr]);
	}

	if (!dispavg) {

		printf("%-11s %9u %9u %9u %9u\n", timestamp[curr],
		       snsc->tcp6_inuse,
		       snsc->udp6_inuse,
		       snsc->raw6_inuse,
		       snsc->frag6_inuse);


		avg_tcp6_inuse  += snsc->tcp6_inuse;
		avg_udp6_inuse  += snsc->udp6_inuse;
		avg_raw6_inuse  += snsc->raw6_inuse;
		avg_frag6_inuse += snsc->frag6_inuse;
	}
	else {

		printf("%-11s %9.0f %9.0f %9.0f %9.0f\n", timestamp[curr],
		       (double) avg_tcp6_inuse  / avg_count,
		       (double) avg_udp6_inuse  / avg_count,
		       (double) avg_raw6_inuse  / avg_count,
		       (double) avg_frag6_inuse / avg_count);


		avg_tcp6_inuse = avg_udp6_inuse = avg_raw6_inuse = avg_frag6_inuse = 0;
	}
}
