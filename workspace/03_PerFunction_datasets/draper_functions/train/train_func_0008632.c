knot_packet_free_tmp_rrsets(knot_packet_t *pkt)
{
	if (pkt == NULL) {
		return;
	}

	for (int i = 0; i < pkt->tmp_rrsets_count; ++i) {
dbg_packet_exec(
		char *name = knot_dname_to_str(
			(((knot_rrset_t **)(pkt->tmp_rrsets))[i])->owner);
		dbg_packet_verb("Freeing tmp RRSet on ptr: %p (ptr to ptr:"
		       " %p, type: %u, owner: %s)\n",
		       (((knot_rrset_t **)(pkt->tmp_rrsets))[i]),
		       &(((knot_rrset_t **)(pkt->tmp_rrsets))[i]),
		       (((knot_rrset_t **)(pkt->tmp_rrsets))[i])->type,
		       name);
		free(name);
);


		knot_rrset_deep_free(
			&(((knot_rrset_t **)(pkt->tmp_rrsets))[i]), 1);
	}
}
