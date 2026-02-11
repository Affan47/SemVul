rcutorture_booster_init(int cpu)
{
	int retval;

	if (boost_tasks[cpu] != NULL)
		return 0;


	mutex_lock(&boost_mutex);
	VERBOSE_TOROUT_STRING("Creating rcu_torture_boost task");
	boost_tasks[cpu] = kthread_create_on_node(rcu_torture_boost, NULL,
						  cpu_to_node(cpu),
						  "rcu_torture_boost");
	if (IS_ERR(boost_tasks[cpu])) {
		retval = PTR_ERR(boost_tasks[cpu]);
		VERBOSE_TOROUT_STRING("rcu_torture_boost task create failed");
		n_rcu_torture_boost_ktrerror++;
		boost_tasks[cpu] = NULL;
		mutex_unlock(&boost_mutex);
		return retval;
	}
	kthread_bind(boost_tasks[cpu], cpu);
	wake_up_process(boost_tasks[cpu]);
	mutex_unlock(&boost_mutex);
	return 0;
}
