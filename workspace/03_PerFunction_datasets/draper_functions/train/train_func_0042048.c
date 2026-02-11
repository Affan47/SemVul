__add_candidate(struct super_block *sb, struct gc_candidate *cand)
{
	struct logfs_super *super = logfs_super(sb);
	u32 full = super->s_segsize - LOGFS_SEGMENT_RESERVE;

	if (cand->valid == 0) {

		log_gc_noisy("add reserve segment %x (ec %x) at %llx\n",
				cand->segno, cand->erase_count,
				dev_ofs(sb, cand->segno, 0));
		cand = add_list(cand, &super->s_reserve_list);
		if (cand) {
			log_gc_noisy("add free segment %x (ec %x) at %llx\n",
					cand->segno, cand->erase_count,
					dev_ofs(sb, cand->segno, 0));
			cand = add_list(cand, &super->s_free_list);
		}
	} else {

		if (cand->valid < full)
			cand = add_list(cand, &super->s_low_list[cand->dist]);


		if (cand)
			cand = add_list(cand, &super->s_ec_list);
	}
	if (cand)
		free_candidate(sb, cand);
}
