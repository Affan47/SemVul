kretprobe_table_unlock(unsigned long hash,
				   unsigned long *flags)
__releases(hlist_lock)
{
	raw_spinlock_t *hlist_lock = kretprobe_table_lock_ptr(hash);
	raw_spin_unlock_irqrestore(hlist_lock, *flags);
}
