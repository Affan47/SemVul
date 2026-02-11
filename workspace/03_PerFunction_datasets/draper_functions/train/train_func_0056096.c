nfs4_free_slot(struct nfs4_slot_table *tbl, struct nfs4_slot *slot)
{
	u32 slotid = slot->slot_nr;


	__clear_bit(slotid, tbl->used_slots);


	if (slotid == tbl->highest_used_slotid) {
		u32 new_max = find_last_bit(tbl->used_slots, slotid);
		if (new_max < slotid)
			tbl->highest_used_slotid = new_max;
		else {
			tbl->highest_used_slotid = NFS4_NO_SLOT;
			nfs4_slot_tbl_drain_complete(tbl);
		}
	}
	dprintk("%s: slotid %u highest_used_slotid %u\n", __func__,
		slotid, tbl->highest_used_slotid);
}
