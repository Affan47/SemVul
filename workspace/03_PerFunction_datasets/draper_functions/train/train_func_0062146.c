handle_qstat_req(struct gnutella_node *n, const struct vmsg *vmsg,
	const char *unused_payload, size_t unused_size)
{
	uint32 kept;
	const struct guid *muid = gnutella_header_get_muid(&n->header);

	(void) unused_payload;
	(void) unused_size;


	if (!vmsg_from_tcp(n, vmsg))
		return;

	if (!search_get_kept_results_by_muid(muid, &kept)) {


		if (GNET_PROPERTY(vmsg_debug)) {
			g_warning("VMSG could not find matching search for #%s",
				guid_hex_str(muid));
		}
		kept = 0xffffU;
	} else {


		if (search_running_guess(muid))
			kept = 0xffffU;
		else
			kept = MIN(kept, 0xfffeU);
	}

	vmsg_send_qstat_answer(n, muid, kept);
}
