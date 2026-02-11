rcu_verify_early_boot_tests(void)
{
	int ret = 0;
	int early_boot_test_counter = 0;

	if (rcu_self_test) {
		early_boot_test_counter++;
		rcu_barrier();
	}
	if (rcu_self_test_bh) {
		early_boot_test_counter++;
		rcu_barrier_bh();
	}
	if (rcu_self_test_sched) {
		early_boot_test_counter++;
		rcu_barrier_sched();
	}

	if (rcu_self_test_counter != early_boot_test_counter) {
		WARN_ON(1);
		ret = -1;
	}

	return ret;
}
