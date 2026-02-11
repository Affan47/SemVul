nfs4_grow_slot_table(struct nfs4_slot_table *tbl,
		 u32 max_reqs, u32 ivalue)
{
	if (max_reqs <= tbl->max_slots)
		return 0;
	if (!IS_ERR(nfs4_find_or_create_slot(tbl, max_reqs - 1, ivalue, GFP_NOFS)))
		return 0;
	return -ENOMEM;
}
