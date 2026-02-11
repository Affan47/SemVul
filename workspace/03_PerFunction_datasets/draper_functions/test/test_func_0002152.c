nat_t_match_nat_d_payload(struct message *msg, struct sockaddr *sa)
{
	struct payload *p;
	u_int8_t *hbuf;
	size_t	 hbuflen;
	int	 found = 0;


	if ((p = payload_first(msg, ISAKMP_PAYLOAD_NAT_D_DRAFT)) == NULL &&
	    (p = payload_first(msg, ISAKMP_PAYLOAD_NAT_D)) == NULL)
		return 1;

	hbuf = nat_t_generate_nat_d_hash(msg, sa, &hbuflen);
	if (!hbuf)
		return 0;

	while (p) {
		if (GET_ISAKMP_GEN_LENGTH (p->p) !=
		    hbuflen + ISAKMP_NAT_D_DATA_OFF)
			continue;

		if (memcmp(p->p + ISAKMP_NAT_D_DATA_OFF, hbuf, hbuflen) == 0) {
			found++;
			break;
		}
		p = TAILQ_NEXT(p, link);
	}
	free(hbuf);
	return found;
}
