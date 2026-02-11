chargen_dg(int s, servtab_t *sep)
{
	int len;
	char text[LINESIZ + 2];
	len_and_sockaddr *lsa = alloca(LSA_LEN_SIZE + sep->se_lsa->len);


	lsa->len = sep->se_lsa->len;
	if (recvfrom(s, text, sizeof(text), MSG_DONTWAIT, &lsa->u.sa, &lsa->len) < 0)
		return;

	if (!end_ring) {
		init_ring();
		ring_pos = ring;
	}

	len = end_ring - ring_pos;
	if (len >= LINESIZ)
		memmove(text, ring_pos, LINESIZ);
	else {
		memmove(text, ring_pos, len);
		memmove(text + len, ring, LINESIZ - len);
	}
	if (++ring_pos == end_ring)
		ring_pos = ring;
	text[LINESIZ] = '\r';
	text[LINESIZ + 1] = '\n';
	sendto(s, text, sizeof(text), 0, &lsa->u.sa, lsa->len);
}
