r600_cs_parse_packet0(struct radeon_cs_parser *p,
				struct radeon_cs_packet *pkt)
{
	unsigned reg, i;
	unsigned idx;
	int r;

	idx = pkt->idx + 1;
	reg = pkt->reg;
	for (i = 0; i <= pkt->count; i++, idx++, reg += 4) {
		r = r600_packet0_check(p, pkt, idx, reg);
		if (r) {
			return r;
		}
	}
	return 0;
}
