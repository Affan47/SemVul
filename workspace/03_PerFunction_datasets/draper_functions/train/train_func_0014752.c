ikev1_attrmap_print(netdissect_options *ndo,
		    const u_char *p, const u_char *ep,
		    const struct attrmap *map, size_t nmap)
{
	u_int16_t *q;
	int totlen;
	u_int32_t t, v;

	q = (u_int16_t *)p;
	if (p[0] & 0x80)
		totlen = 4;
	else
		totlen = 4 + EXTRACT_16BITS(&q[1]);
	if (ep < p + totlen) {
		ND_PRINT((ndo,"[|attr]"));
		return ep + 1;
	}

	ND_PRINT((ndo,"("));
	t = EXTRACT_16BITS(&q[0]) & 0x7fff;
	if (map && t < nmap && map[t].type)
		ND_PRINT((ndo,"type=%s ", map[t].type));
	else
		ND_PRINT((ndo,"type=#%d ", t));
	if (p[0] & 0x80) {
		ND_PRINT((ndo,"value="));
		v = EXTRACT_16BITS(&q[1]);
		if (map && t < nmap && v < map[t].nvalue && map[t].value[v])
			ND_PRINT((ndo,"%s", map[t].value[v]));
		else
			rawprint(ndo, (caddr_t)&q[1], 2);
	} else {
		ND_PRINT((ndo,"len=%d value=", EXTRACT_16BITS(&q[1])));
		rawprint(ndo, (caddr_t)&p[4], EXTRACT_16BITS(&q[1]));
	}
	ND_PRINT((ndo,")"));
	return p + totlen;
}
