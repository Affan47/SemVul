_mosquitto_packet_cleanup(struct _mosquitto_packet *packet)
{
	if(!packet) return;


	packet->command = 0;
	packet->have_remaining = 0;
	packet->remaining_count = 0;
	packet->remaining_mult = 1;
	packet->remaining_length = 0;
	if(packet->payload) _mosquitto_free(packet->payload);
	packet->payload = NULL;
	packet->to_process = 0;
	packet->pos = 0;
}
