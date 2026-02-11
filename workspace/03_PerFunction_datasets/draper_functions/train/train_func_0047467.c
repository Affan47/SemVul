mqtt3_bridge_packet_cleanup(struct mosquitto *context)
{
	struct _mosquitto_packet *packet;
	if(!context) return;

	_mosquitto_packet_cleanup(context->current_out_packet);
    while(context->out_packet){
		_mosquitto_packet_cleanup(context->out_packet);
		packet = context->out_packet;
		context->out_packet = context->out_packet->next;
		_mosquitto_free(packet);
	}

	_mosquitto_packet_cleanup(&(context->in_packet));
}
