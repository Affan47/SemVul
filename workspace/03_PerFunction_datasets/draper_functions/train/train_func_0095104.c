guess_request_qk(const gnet_host_t *host, bool intro)
{
	const gnet_host_t *h;
	bool sent;

	h = atom_host_get(host);

	sent = guess_request_qk_full(NULL, host, intro,
		guess_qk_reply, deconstify_pointer(h));

	if (!sent)
		atom_host_free(h);

	return sent;
}
