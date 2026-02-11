fw_shutdown_notify(struct notifier_block *unused1,
			      unsigned long unused2, void *unused3)
{
	mutex_lock(&fw_lock);
	while (!list_empty(&pending_fw_head))
		__fw_load_abort(list_first_entry(&pending_fw_head,
					       struct firmware_buf,
					       pending_list));
	mutex_unlock(&fw_lock);
	return NOTIFY_DONE;
}
