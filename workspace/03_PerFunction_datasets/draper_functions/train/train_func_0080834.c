handle_deliver_status_report_response(Octstr *packet, Octstr *out, int sequence) {
	awaiting_response = 0;
	if (logging == LOG_packets)
		printf("RCV: Deliver status report response\n");

}
