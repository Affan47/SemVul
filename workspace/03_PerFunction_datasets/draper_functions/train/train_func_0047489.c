mirror_show_queue(unsigned long target)
{
	unsigned long ms, rlist, wlist, rhead, whead;
	unsigned long rh, quis_head, rcov_head, quis_next, rcov_next;


	GET_VALUE(target, dm_target, private, ms);


	GET_ADDR(ms, mirror_set, reads, rlist);
	GET_ADDR(ms, mirror_set, writes, wlist);


	GET_VALUE(rlist, bio_list, head, rhead);
	GET_VALUE(wlist, bio_list, head, whead);
	fprintf(fp, "  %s", rhead ? "reads" : "(reads)");
	fprintf(fp, " %s", whead ? "writes" : "(writes)");


	GET_ADDR(ms, mirror_set, rh, rh);


	GET_ADDR(rh, region_hash, quiesced_regions, quis_head);
	GET_ADDR(rh, region_hash, recovered_regions, rcov_head);


	quis_next = get_next_from_list_head(quis_head);
	rcov_next = get_next_from_list_head(rcov_head);

	fprintf(fp, " %s", quis_next != quis_head ? "quiesced" : "(quiesced)");
	fprintf(fp, " %s", rcov_next != rcov_head ? "recovered" : "(recovered)");
}
