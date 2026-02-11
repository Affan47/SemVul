writeByte(donkeyMsg *m, unsigned char c) {
	if (!canAdvance(m, 1))
		return;

	m->payload[m->pos] = c;
	m->pos = m->pos + 1;
}
