handle_oob_proxy_veto(struct gnutella_node *n,
	const struct vmsg *vmsg, const char *payload, size_t size)
{
	if (!vmsg_from_tcp(n, vmsg))
		return;

	if (!NODE_IS_LEAF(n)) {
		vmsg_ignore(n, vmsg);
		return;
	}

	if (size > 0 && peek_u8(payload) < 3) {

		n->attrs2 &= ~NODE_A2_NO_OOB_PROXY;
	} else {
		n->attrs2 |= NODE_A2_NO_OOB_PROXY;
	}

	return;
}
