kcore_callback(struct notifier_block *self,
				    unsigned long action, void *arg)
{
	switch (action) {
	case MEM_ONLINE:
	case MEM_OFFLINE:
		write_lock(&kclist_lock);
		kcore_need_update = 1;
		write_unlock(&kclist_lock);
	}
	return NOTIFY_OK;
}
