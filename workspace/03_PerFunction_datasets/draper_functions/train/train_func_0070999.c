hdhomerun_pkt_write_u32(struct hdhomerun_pkt_t *pkt, uint32_t v)
{
	*pkt->pos++ = (uint8_t)(v >> 24);
	*pkt->pos++ = (uint8_t)(v >> 16);
	*pkt->pos++ = (uint8_t)(v >> 8);
	*pkt->pos++ = (uint8_t)(v >> 0);

	if (pkt->pos > pkt->end) {
		pkt->end = pkt->pos;
	}
}
