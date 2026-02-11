bnxt_free_ntp_fltrs(struct bnxt *bp, bool irq_reinit)
{
#ifdef CONFIG_RFS_ACCEL
	int i;


	for (i = 0; i < BNXT_NTP_FLTR_HASH_SIZE; i++) {
		struct hlist_head *head;
		struct hlist_node *tmp, __maybe_unused *nxt;
		struct bnxt_ntuple_filter *fltr;

		head = &bp->ntp_fltr_hash_tbl[i];
		__hlist_for_each_entry_safe(fltr, nxt, tmp, head, hash) {
			hlist_del(&fltr->hash);
			kfree(fltr);
		}
	}
	if (irq_reinit) {
		kfree(bp->ntp_fltr_bmap);
		bp->ntp_fltr_bmap = NULL;
	}
	bp->ntp_fltr_count = 0;
#endif
}
