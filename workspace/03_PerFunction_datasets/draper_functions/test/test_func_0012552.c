resolve(const char *h)
{
	struct hostent *hp;
	in_addr_t	ip;

	if ((ip = inet_addr(h)) != INADDR_NONE)
		return ip;

	if ((hp = gethostbyname(h)) == NULL)
		return INADDR_NONE;
	else {
		(void) memcpy(&ip, hp->h_addr, hp->h_length);
		return ip;
	}
}
