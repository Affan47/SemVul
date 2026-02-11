exchange_lookup(u_int8_t *msg, int phase2)
{
	struct exchange *exchange;
	u_int16_t       bucket = 0;
	u_int8_t       *cp;
	int             i;


	for (i = 0; i < ISAKMP_HDR_COOKIES_LEN; i += 2) {
		cp = msg + ISAKMP_HDR_COOKIES_OFF + i;

		bucket ^= cp[0] | cp[1] << 8;
	}
	if (phase2)
		for (i = 0; i < ISAKMP_HDR_MESSAGE_ID_LEN; i += 2) {
			cp = msg + ISAKMP_HDR_MESSAGE_ID_OFF + i;

			bucket ^= cp[0] | cp[1] << 8;
		}
	bucket &= bucket_mask;
	for (exchange = LIST_FIRST(&exchange_tab[bucket]);
	    exchange && (memcmp(msg + ISAKMP_HDR_COOKIES_OFF,
		exchange->cookies, ISAKMP_HDR_COOKIES_LEN) != 0 ||
		(phase2 && memcmp(msg + ISAKMP_HDR_MESSAGE_ID_OFF,
		    exchange->message_id, ISAKMP_HDR_MESSAGE_ID_LEN) != 0) ||
		(!phase2 && !zero_test(msg + ISAKMP_HDR_MESSAGE_ID_OFF,
		    ISAKMP_HDR_MESSAGE_ID_LEN)));
	     exchange = LIST_NEXT(exchange, link))
		;

	return exchange;
}
