sk_peer_label(struct sock *sk)
{
	struct sock *peer_sk;
	struct aa_sk_ctx *ctx = SK_CTX(sk);

	if (ctx->peer)
		return ctx->peer;

	if (sk->sk_family != PF_UNIX)
		return ERR_PTR(-ENOPROTOOPT);


	peer_sk = unix_peer(sk);
	if (peer_sk) {
		ctx = SK_CTX(peer_sk);
		if (ctx->label)
			return ctx->label;
	}

	return ERR_PTR(-ENOPROTOOPT);
}
