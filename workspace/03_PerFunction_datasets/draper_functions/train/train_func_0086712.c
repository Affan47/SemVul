synchronize_rcu_tasks(void)
{

	RCU_LOCKDEP_WARN(!rcu_scheduler_active,
			 "synchronize_rcu_tasks called too soon");


	wait_rcu_gp(call_rcu_tasks);
}
