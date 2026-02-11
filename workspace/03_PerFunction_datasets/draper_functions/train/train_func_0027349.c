address_match(struct sockaddr *sa1, struct sockaddr *sa2)
{
	if (sa1->sa_family == AF_INET)
		return ((struct sockaddr_in *) sa1)->sin_addr.s_addr ==
			((struct sockaddr_in *) sa2)->sin_addr.s_addr;
	else {
		struct in6_addr *a1, *a2;

		a1 = &((struct sockaddr_in6 *) sa1)->sin6_addr;
		a2 = &((struct sockaddr_in6 *) sa2)->sin6_addr;

		return (a1->s6_addr32[0] == a2->s6_addr32[0] &&
			a1->s6_addr32[1] == a2->s6_addr32[1] &&
			a1->s6_addr32[2] == a2->s6_addr32[2] &&
			a1->s6_addr32[3] == a2->s6_addr32[3]);
	}

	return 0;
}
