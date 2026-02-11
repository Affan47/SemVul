netmask_match_v6(struct sockaddr *sa1, struct sockaddr *sa2, uint32_t mbit)
{
	uint16_t mask, a1[8], a2[8];
	int i;

	for (i = 0; i < 8; i++) {
		a1[i] = ntohs(((struct sockaddr_in6 *) sa1)->sin6_addr.s6_addr16[i]);
		a2[i] = ntohs(((struct sockaddr_in6 *) sa2)->sin6_addr.s6_addr16[i]);
	}

	for (i = 0; i < mbit / 16; i++)
		if (a1[i] ^ a2[i])
			return 0;

	if (mbit % 16) {
		mask = ~((1 << (16 - (mbit % 16))) - 1);
		if ((mask & a1[mbit / 16]) ^ (mask & a2[mbit / 16]))
			return 0;
	}

	return 1;
}
