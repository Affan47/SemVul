dns_parse_answer(void *context,
	int class, int type, unsigned char *answer, int len,
	int (*callback)(void *context, unsigned char *answer, int len, unsigned char *fullanswer))
{
	unsigned char *fullanswer = answer;
	struct dn_answer *ans;
	dns_HEADER *h;
	int ret = 0;
	int res;
	int x;

	h = (dns_HEADER *)answer;
	answer += sizeof(dns_HEADER);
	len -= sizeof(dns_HEADER);

	for (x = 0; x < ntohs(h->qdcount); x++) {
		if ((res = skip_name(answer, len)) < 0) {
			ast_log(LOG_WARNING, "Couldn't skip over name\n");
			return -1;
		}
		answer += res + 4;
		len -= res + 4;
		if (len < 0) {
			ast_log(LOG_WARNING, "Strange query size\n");
			return -1;
		}
	}

	for (x = 0; x < ntohs(h->ancount); x++) {
		if ((res = skip_name(answer, len)) < 0) {
			ast_log(LOG_WARNING, "Failed skipping name\n");
			return -1;
		}
		answer += res;
		len -= res;
		ans = (struct dn_answer *)answer;
		answer += sizeof(struct dn_answer);
		len -= sizeof(struct dn_answer);
		if (len < 0) {
			ast_log(LOG_WARNING, "Strange result size\n");
			return -1;
		}
		if (len < 0) {
			ast_log(LOG_WARNING, "Length exceeds frame\n");
			return -1;
		}

		if (ntohs(ans->class) == class && ntohs(ans->rtype) == type) {
			if (callback) {
				if ((res = callback(context, answer, ntohs(ans->size), fullanswer)) < 0) {
					ast_log(LOG_WARNING, "Failed to parse result\n");
					return -1;
				}
				ret = 1;
			}
		}
		answer += ntohs(ans->size);
		len -= ntohs(ans->size);
	}
	return ret;
}
