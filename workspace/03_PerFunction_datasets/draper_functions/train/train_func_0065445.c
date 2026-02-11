prune_bucket(struct nfsd_drc_bucket *b)
{
	struct svc_cacherep *rp, *tmp;
	long freed = 0;

	list_for_each_entry_safe(rp, tmp, &b->lru_head, c_lru) {


		if (rp->c_state == RC_INPROG)
			continue;
		if (atomic_read(&num_drc_entries) <= max_drc_entries &&
		    time_before(jiffies, rp->c_timestamp + RC_EXPIRE))
			break;
		nfsd_reply_cache_free_locked(rp);
		freed++;
	}
	return freed;
}
