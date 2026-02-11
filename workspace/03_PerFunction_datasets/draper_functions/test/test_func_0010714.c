check_question(struct reslist *request, HEADER * header, char *buf, char *eob)
{
	char hostbuf[IRCD_RES_HOSTLEN + 1];
	unsigned char *current;
	int n;

	current = (unsigned char *)buf + sizeof(HEADER);
	if (header->qdcount != 1)
		return 0;
	n = irc_dn_expand((unsigned char *)buf, (unsigned char *)eob, current, hostbuf,
			  sizeof(hostbuf));
	if (n <= 0)
		return 0;
	if (strcasecmp(hostbuf, request->queryname))
		return 0;
	return 1;
}
