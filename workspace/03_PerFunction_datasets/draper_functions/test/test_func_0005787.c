handle_get(Octstr *packet, Octstr *out, int sequence) {
	long number = eat_int_parm(packet, 500, 3);

	if (logging == LOG_packets)
		printf("RCV: Get parameter #%ld\n", number);

	if (number == INT_MIN) {
		send_error(out, 59, sequence, "900", "missing parameter");
	} else if (number == 501) {
		unsigned char buf[TIMESTAMP_MAXLEN];
		make_timestamp(buf, time(NULL));
		if (logging == LOG_packets)
			printf("SND: OK, SMSC timestamp is '%s'\n", buf);
		send_packet(out, 59, sequence,
			    501, buf,
			    0);
	} else {
		send_error(out, 59, sequence, "900", "unknown parameter");
	}
}
