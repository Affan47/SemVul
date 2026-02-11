nfs41_update_target_slotid(struct nfs4_slot_table *tbl,
		struct nfs4_slot *slot,
		struct nfs4_sequence_res *res)
{
	spin_lock(&tbl->slot_tbl_lock);
	if (!nfs41_is_outlier_target_slotid(tbl, res->sr_target_highest_slotid))
		nfs41_set_target_slotid_locked(tbl, res->sr_target_highest_slotid);
	if (tbl->generation == slot->generation)
		nfs41_set_server_slotid_locked(tbl, res->sr_highest_slotid);
	nfs41_set_max_slotid_locked(tbl, res->sr_target_highest_slotid);
	spin_unlock(&tbl->slot_tbl_lock);
}
