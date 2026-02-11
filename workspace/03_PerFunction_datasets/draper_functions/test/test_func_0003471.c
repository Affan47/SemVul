rwsem_can_spin_on_owner(struct rw_semaphore *sem)
{
	struct task_struct *owner;
	bool ret = true;

	if (need_resched())
		return false;

	rcu_read_lock();
	owner = READ_ONCE(sem->owner);
	if (!owner) {
		long count = READ_ONCE(sem->count);


		if (count & RWSEM_ACTIVE_MASK)
			ret = false;
		goto done;
	}

	ret = owner->on_cpu;
done:
	rcu_read_unlock();
	return ret;
}
