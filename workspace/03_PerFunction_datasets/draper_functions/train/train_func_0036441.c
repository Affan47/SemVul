nfsd4_layout_lm_change(struct file_lock *onlist, int arg,
		struct list_head *dispose)
{
	BUG_ON(!(arg & F_UNLCK));
	return lease_modify(onlist, arg, dispose);
}
