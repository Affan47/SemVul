profile_peer_perm(struct aa_profile *profile, const char *op, u32 request,
			     struct sock *sk, struct sock *peer_sk,
			     struct aa_label *peer_label,
			     struct common_audit_data *sa)
{
	unsigned int state;

	AA_BUG(!profile);
	AA_BUG(profile_unconfined(profile));
	AA_BUG(!sk);
	AA_BUG(!peer_sk);
	AA_BUG(UNIX_FS(peer_sk));

	state = PROFILE_MEDIATES_AF(profile, AF_UNIX);
	if (state) {
		struct aa_sk_ctx *peer_ctx = SK_CTX(peer_sk);
		struct aa_profile *peerp;
		struct sockaddr_un *addr = NULL;
		int len = 0;
		if (unix_sk(peer_sk)->addr) {
			addr = unix_sk(peer_sk)->addr->name;
			len = unix_sk(peer_sk)->addr->len;
		}
		state = match_to_peer(profile, state, unix_sk(sk),
				      addr, len, &aad(sa)->info);
		if (!peer_label)
			peer_label = peer_ctx->label;
		return fn_for_each_in_ns(peer_label, peerp,
				   match_label(profile, peerp, state, request,
					       sa));
	}

	return aa_profile_af_sk_perm(profile, sa, request, sk);
}
