nfs41_set_max_slotid_locked(struct nfs4_slot_table *tbl,
		u32 target_highest_slotid)
{
	u32 max_slotid;

	max_slotid = min(NFS4_MAX_SLOT_TABLE - 1, target_highest_slotid);
	if (max_slotid > tbl->server_highest_slotid)
		max_slotid = tbl->server_highest_slotid;
	if (max_slotid > tbl->target_highest_slotid)
		max_slotid = tbl->target_highest_slotid;
	tbl->max_slotid = max_slotid;
	nfs41_wake_slot_table(tbl);
}
