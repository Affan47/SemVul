sdp_create(int sk, uint32_t flags)
{
	sdp_session_t *session;
	struct sdp_transaction *t;

	session = malloc(sizeof(sdp_session_t));
	if (!session) {
		errno = ENOMEM;
		return NULL;
	}
	memset(session, 0, sizeof(*session));

	session->flags = flags;
	session->sock = sk;

	t = malloc(sizeof(struct sdp_transaction));
	if (!t) {
		errno = ENOMEM;
		free(session);
		return NULL;
	}
	memset(t, 0, sizeof(*t));

	session->priv = t;

	return session;
}
