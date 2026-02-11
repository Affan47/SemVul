sctp_init(struct xt_entry_match *m)
{
	int i;
	struct xt_sctp_info *einfo = (struct xt_sctp_info *)m->data;

	for (i = 0; i < XT_NUM_SCTP_FLAGS; i++) {
		einfo->flag_info[i].chunktype = -1;
	}
}
