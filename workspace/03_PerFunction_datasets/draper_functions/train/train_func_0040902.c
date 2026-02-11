erst_get_record_count(void)
{
	ssize_t count;
	unsigned long flags;

	if (erst_disable)
		return -ENODEV;

	raw_spin_lock_irqsave(&erst_lock, flags);
	count = __erst_get_record_count();
	raw_spin_unlock_irqrestore(&erst_lock, flags);

	return count;
}
