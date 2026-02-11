hdhomerun_video_stats_ts_pkt(struct hdhomerun_video_sock_t *vs, uint8_t *ptr)
{
	uint16_t packet_identifier = ((uint16_t)(ptr[1] & 0x1F) << 8) | (uint16_t)ptr[2];
	if (packet_identifier == 0x1FFF) {
		return;
	}

	bool_t transport_error = ptr[1] >> 7;
	if (transport_error) {
		vs->transport_error_count++;
		vs->sequence[packet_identifier] = 0xFF;
		return;
	}

	uint8_t sequence = ptr[3] & 0x0F;

	uint8_t previous_sequence = vs->sequence[packet_identifier];
	vs->sequence[packet_identifier] = sequence;

	if (previous_sequence == 0xFF) {
		return;
	}
	if (sequence == ((previous_sequence + 1) & 0x0F)) {
		return;
	}
	if (sequence == previous_sequence) {
		return;
	}

	vs->sequence_error_count++;
}
