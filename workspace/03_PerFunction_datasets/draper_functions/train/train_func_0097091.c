hdhomerun_pkt_read_var_length(struct hdhomerun_pkt_t *pkt)
{
	size_t length;

	if (pkt->pos + 1 > pkt->end) {
		return (size_t)-1;
	}

	length = (size_t)*pkt->pos++;
	if (length & 0x0080) {
		if (pkt->pos + 1 > pkt->end) {
			return (size_t)-1;
		}

		length &= 0x007F;
		length |= (size_t)*pkt->pos++ << 7;
	}

	return length;
}
