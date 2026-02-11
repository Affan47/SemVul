knot_packet_answer_rrset(
	const knot_packet_t *packet, short pos)
{
	if (packet == NULL || pos >= packet->an_rrsets) {
		return NULL;
	}

	return packet->answer[pos];
}
