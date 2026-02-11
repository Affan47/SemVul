nfs41_set_target_slotid_locked(struct nfs4_slot_table *tbl,
		u32 target_highest_slotid)
{
	if (tbl->target_highest_slotid == target_highest_slotid)
		return;
	tbl->target_highest_slotid = target_highest_slotid;
	tbl->generation++;
}
