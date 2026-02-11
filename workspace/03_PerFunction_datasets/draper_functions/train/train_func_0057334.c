iwl_mvm_find_free_queue(struct iwl_mvm *mvm, u8 minq, u8 maxq)
{
	int i;

	lockdep_assert_held(&mvm->queue_info_lock);

	for (i = minq; i <= maxq; i++)
		if (mvm->queue_info[i].hw_queue_refcount == 0 &&
		    !mvm->queue_info[i].setup_reserved)
			return i;

	return -ENOSPC;
}
