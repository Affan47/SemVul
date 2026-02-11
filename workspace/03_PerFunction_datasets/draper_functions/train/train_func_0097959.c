free_uid(struct user_struct *up)
{
	unsigned long flags;

	if (!up)
		return;

	local_irq_save(flags);
	if (atomic_dec_and_lock(&up->__count, &uidhash_lock))
		free_user(up, flags);
	else
		local_irq_restore(flags);
}
