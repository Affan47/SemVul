payload_first(struct message *msg, u_int8_t payload)
{
	if (payload_map[payload])
		return TAILQ_FIRST(&msg->payload[payload_map[payload]]);
	else
		return 0;
}
