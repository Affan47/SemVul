sctp_save(const void *ip, const struct xt_entry_match *match)
{
	const struct xt_sctp_info *einfo =
		(const struct xt_sctp_info *)match->data;

	if (einfo->flags & XT_SCTP_SRC_PORTS) {
		if (einfo->invflags & XT_SCTP_SRC_PORTS)
			printf(" !");
		if (einfo->spts[0] != einfo->spts[1])
			printf(" --sport %u:%u",
			       einfo->spts[0], einfo->spts[1]);
		else
			printf(" --sport %u", einfo->spts[0]);
	}

	if (einfo->flags & XT_SCTP_DEST_PORTS) {
		if (einfo->invflags & XT_SCTP_DEST_PORTS)
			printf(" !");
		if (einfo->dpts[0] != einfo->dpts[1])
			printf(" --dport %u:%u",
			       einfo->dpts[0], einfo->dpts[1]);
		else
			printf(" --dport %u", einfo->dpts[0]);
	}

	if (einfo->flags & XT_SCTP_CHUNK_TYPES) {
		if (einfo->invflags & XT_SCTP_CHUNK_TYPES)
			printf(" !");
		printf(" --chunk-types");

		print_chunks(einfo, 0);
	}
}
