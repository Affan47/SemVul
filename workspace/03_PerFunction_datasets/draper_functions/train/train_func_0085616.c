match_to_sk(struct aa_profile *profile,
				unsigned int state, struct unix_sock *u,
				const char **info)
{
	struct sockaddr_un *addr = NULL;
	int addrlen = 0;

	if (u->addr) {
		addr = u->addr->name;
		addrlen = u->addr->len;
	}

	return match_to_local(profile, state, u->sk.sk_type, u->sk.sk_protocol,
			      addr, addrlen, info);
}
