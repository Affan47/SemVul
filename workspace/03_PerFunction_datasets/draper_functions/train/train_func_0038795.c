try_to_take_rt_mutex(struct rt_mutex *lock, struct task_struct *task,
				struct rt_mutex_waiter *waiter)
{
	unsigned long flags;


	mark_rt_mutex_waiters(lock);


	if (rt_mutex_owner(lock))
		return 0;


	if (waiter) {


		if (waiter != rt_mutex_top_waiter(lock))
			return 0;


		rt_mutex_dequeue(lock, waiter);

	} else {


		if (rt_mutex_has_waiters(lock)) {


			if (task->prio >= rt_mutex_top_waiter(lock)->prio)
				return 0;


		} else {


			goto takeit;
		}
	}


	raw_spin_lock_irqsave(&task->pi_lock, flags);
	task->pi_blocked_on = NULL;


	if (rt_mutex_has_waiters(lock))
		rt_mutex_enqueue_pi(task, rt_mutex_top_waiter(lock));
	raw_spin_unlock_irqrestore(&task->pi_lock, flags);

takeit:

	debug_rt_mutex_lock(lock);


	rt_mutex_set_owner(lock, task);

	rt_mutex_deadlock_account_lock(lock, task);

	return 1;
}
