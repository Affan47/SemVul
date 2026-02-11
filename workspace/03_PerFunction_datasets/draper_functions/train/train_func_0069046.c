chap_auth_with_peer(int unit, char *our_name, int digest_code)
{
	struct chap_client_state *cs = &client;
	struct chap_digest_type *dp;

	if (cs->flags & AUTH_STARTED) {
		error("CHAP: authentication with peer already started!");
		return;
	}
	for (dp = chap_digests; dp != NULL; dp = dp->next)
		if (dp->code == digest_code)
			break;
	if (dp == NULL)
		fatal("CHAP digest 0x%x requested but not available",
		      digest_code);

	cs->digest = dp;
	cs->name = our_name;
	cs->flags |= AUTH_STARTED;
}
