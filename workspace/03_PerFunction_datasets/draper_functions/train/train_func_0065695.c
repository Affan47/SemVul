apparmor_unix_stream_connect(struct sock *sk, struct sock *peer_sk,
					struct sock *newsk)
{
	struct aa_sk_ctx *sk_ctx = SK_CTX(sk);
	struct aa_sk_ctx *peer_ctx = SK_CTX(peer_sk);
	struct aa_sk_ctx *new_ctx = SK_CTX(newsk);
	struct aa_label *label;
	struct path *path;
	int error;

	label = aa_begin_current_label(NO_UPDATE);
	error = aa_unix_peer_perm(label, OP_CONNECT,
				(AA_MAY_CONNECT | AA_MAY_SEND | AA_MAY_RECEIVE),
				  sk, peer_sk, NULL);
	if (!UNIX_FS(peer_sk)) {
		last_error(error,
			aa_unix_peer_perm(peer_ctx->label, OP_CONNECT,
				(AA_MAY_ACCEPT | AA_MAY_SEND | AA_MAY_RECEIVE),
				peer_sk, sk, label));
	}
	aa_end_current_label(label);

	if (error)
		return error;


	if (!new_ctx->label)
		new_ctx->label = aa_get_label(peer_ctx->label);


	if (new_ctx->peer)
		aa_put_label(new_ctx->peer);

	if (sk_ctx->peer)
		aa_put_label(sk_ctx->peer);

	new_ctx->peer = aa_get_label(sk_ctx->label);
	sk_ctx->peer = aa_get_label(peer_ctx->label);

	path = UNIX_FS_CONN_PATH(sk, peer_sk);
	if (path) {
		new_ctx->path = *path;
		sk_ctx->path = *path;
		path_get(path);
		path_get(path);
	}
	return 0;
}
