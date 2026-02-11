handle_qstat_answer(struct gnutella_node *n,
	const struct vmsg *vmsg, const char *payload, size_t size)
{
	uint16 kept;

	if (VMSG_SHORT_SIZE(n, vmsg, size, 2))
		return;


	kept = peek_le16(payload);
	dq_got_query_status(gnutella_header_get_muid(&n->header), NODE_ID(n), kept);
}
