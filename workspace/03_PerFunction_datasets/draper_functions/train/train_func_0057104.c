unlock_all_device_hash_locks_irq(struct r5conf *conf)
{
	int i;
	spin_unlock(&conf->device_lock);
	for (i = NR_STRIPE_HASH_LOCKS; i; i--)
		spin_unlock(conf->hash_locks + i - 1);
	local_irq_enable();
}
