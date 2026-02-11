aodv_v6_draft_01_rreq(const union aodv *ap, const u_char *dat, u_int length)
#else
aodv_v6_draft_01_rreq(const union aodv *ap _U_, const u_char *dat _U_,
    u_int length)
#endif
{
#ifdef INET6
	u_int i;

	if (snapend < dat) {
		printf(" [|aodv]");
		return;
	}
	i = min(length, (u_int)(snapend - dat));
	if (i < sizeof(ap->rreq6_draft_01)) {
		printf(" [|rreq6]");
		return;
	}
	i -= sizeof(ap->rreq6_draft_01);
	printf(" rreq %u %s%s%s%s%shops %u id 0x%08lx\n"
	    "\tdst %s seq %lu src %s seq %lu", length,
	    ap->rreq6_draft_01.rreq_type & RREQ_JOIN ? "[J]" : "",
	    ap->rreq6_draft_01.rreq_type & RREQ_REPAIR ? "[R]" : "",
	    ap->rreq6_draft_01.rreq_type & RREQ_GRAT ? "[G]" : "",
	    ap->rreq6_draft_01.rreq_type & RREQ_DEST ? "[D]" : "",
	    ap->rreq6_draft_01.rreq_type & RREQ_UNKNOWN ? "[U] " : " ",
	    ap->rreq6_draft_01.rreq_hops,
	    (unsigned long)EXTRACT_32BITS(&ap->rreq6_draft_01.rreq_id),
	    ip6addr_string(&ap->rreq6_draft_01.rreq_da),
	    (unsigned long)EXTRACT_32BITS(&ap->rreq6_draft_01.rreq_ds),
	    ip6addr_string(&ap->rreq6_draft_01.rreq_oa),
	    (unsigned long)EXTRACT_32BITS(&ap->rreq6_draft_01.rreq_os));
	if (i >= sizeof(struct aodv_ext))
		aodv_extension((void *)(&ap->rreq6_draft_01 + 1), i);
#else
	printf(" rreq %u", length);
#endif
}
