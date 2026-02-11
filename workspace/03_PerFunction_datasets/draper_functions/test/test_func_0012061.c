nego_attempt_rdp(rdpNego* nego)
{
	nego->requested_protocols = PROTOCOL_RDP;

	DEBUG_NEGO("Attempting RDP security");

	nego_tcp_connect(nego);
	nego_send_negotiation_request(nego);

	nego_recv_response(nego);
}
