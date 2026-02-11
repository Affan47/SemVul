iwl_mvm_async_handlers_wk(struct work_struct *wk)
{
	struct iwl_mvm *mvm =
		container_of(wk, struct iwl_mvm, async_handlers_wk);
	struct iwl_async_handler_entry *entry, *tmp;
	struct list_head local_list;

	INIT_LIST_HEAD(&local_list);


	mutex_lock(&mvm->mutex);


	spin_lock_bh(&mvm->async_handlers_lock);
	list_splice_init(&mvm->async_handlers_list, &local_list);
	spin_unlock_bh(&mvm->async_handlers_lock);

	list_for_each_entry_safe(entry, tmp, &local_list, list) {
		entry->fn(mvm, &entry->rxb);
		iwl_free_rxb(&entry->rxb);
		list_del(&entry->list);
		kfree(entry);
	}
	mutex_unlock(&mvm->mutex);
}
