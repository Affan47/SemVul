ws_msg_add(struct ws_msg *m, const char *p, size_t psz, const unsigned char *mask) {


	size_t i;
	m->payload = realloc(m->payload, m->payload_sz + psz);
	memcpy(m->payload + m->payload_sz, p, psz);


	for(i = 0; i < psz && mask; ++i) {
		m->payload[m->payload_sz + i] = (unsigned char)p[i] ^ mask[i%4];
	}


	m->payload_sz += psz;
}
