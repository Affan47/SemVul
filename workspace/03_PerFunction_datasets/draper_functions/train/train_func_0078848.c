rcu_jiffies_till_stall_check(void)
{
	int till_stall_check = READ_ONCE(rcu_cpu_stall_timeout);


	if (till_stall_check < 3) {
		WRITE_ONCE(rcu_cpu_stall_timeout, 3);
		till_stall_check = 3;
	} else if (till_stall_check > 300) {
		WRITE_ONCE(rcu_cpu_stall_timeout, 300);
		till_stall_check = 300;
	}
	return till_stall_check * HZ + RCU_STALL_DELAY_DELTA;
}
