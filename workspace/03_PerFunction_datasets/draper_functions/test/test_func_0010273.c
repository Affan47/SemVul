__nfs41_wake_and_assign_slot(struct nfs4_slot_table *tbl,
		struct nfs4_slot *slot)
{
	if (rpc_wake_up_first(&tbl->slot_tbl_waitq, nfs41_assign_slot, slot))
		return true;
	return false;
}
