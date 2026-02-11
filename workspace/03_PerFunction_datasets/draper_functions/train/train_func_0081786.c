rcu_torture_stats_print(void)
{
	int cpu;
	int i;
	long pipesummary[RCU_TORTURE_PIPE_LEN + 1] = { 0 };
	long batchsummary[RCU_TORTURE_PIPE_LEN + 1] = { 0 };
	static unsigned long rtcv_snap = ULONG_MAX;

	for_each_possible_cpu(cpu) {
		for (i = 0; i < RCU_TORTURE_PIPE_LEN + 1; i++) {
			pipesummary[i] += per_cpu(rcu_torture_count, cpu)[i];
			batchsummary[i] += per_cpu(rcu_torture_batch, cpu)[i];
		}
	}
	for (i = RCU_TORTURE_PIPE_LEN - 1; i >= 0; i--) {
		if (pipesummary[i] != 0)
			break;
	}

	pr_alert("%s%s ", torture_type, TORTURE_FLAG);
	pr_cont("rtc: %p ver: %lu tfle: %d rta: %d rtaf: %d rtf: %d ",
		rcu_torture_current,
		rcu_torture_current_version,
		list_empty(&rcu_torture_freelist),
		atomic_read(&n_rcu_torture_alloc),
		atomic_read(&n_rcu_torture_alloc_fail),
		atomic_read(&n_rcu_torture_free));
	pr_cont("rtmbe: %d rtbke: %ld rtbre: %ld ",
		atomic_read(&n_rcu_torture_mberror),
		n_rcu_torture_boost_ktrerror,
		n_rcu_torture_boost_rterror);
	pr_cont("rtbf: %ld rtb: %ld nt: %ld ",
		n_rcu_torture_boost_failure,
		n_rcu_torture_boosts,
		n_rcu_torture_timers);
	torture_onoff_stats();
	pr_cont("barrier: %ld/%ld:%ld ",
		n_barrier_successes,
		n_barrier_attempts,
		n_rcu_torture_barrier_error);
	pr_cont("cbflood: %ld\n", atomic_long_read(&n_cbfloods));

	pr_alert("%s%s ", torture_type, TORTURE_FLAG);
	if (atomic_read(&n_rcu_torture_mberror) != 0 ||
	    n_rcu_torture_barrier_error != 0 ||
	    n_rcu_torture_boost_ktrerror != 0 ||
	    n_rcu_torture_boost_rterror != 0 ||
	    n_rcu_torture_boost_failure != 0 ||
	    i > 1) {
		pr_cont("%s", "!!! ");
		atomic_inc(&n_rcu_torture_error);
		WARN_ON_ONCE(1);
	}
	pr_cont("Reader Pipe: ");
	for (i = 0; i < RCU_TORTURE_PIPE_LEN + 1; i++)
		pr_cont(" %ld", pipesummary[i]);
	pr_cont("\n");

	pr_alert("%s%s ", torture_type, TORTURE_FLAG);
	pr_cont("Reader Batch: ");
	for (i = 0; i < RCU_TORTURE_PIPE_LEN + 1; i++)
		pr_cont(" %ld", batchsummary[i]);
	pr_cont("\n");

	pr_alert("%s%s ", torture_type, TORTURE_FLAG);
	pr_cont("Free-Block Circulation: ");
	for (i = 0; i < RCU_TORTURE_PIPE_LEN + 1; i++) {
		pr_cont(" %d", atomic_read(&rcu_torture_wcount[i]));
	}
	pr_cont("\n");

	if (cur_ops->stats)
		cur_ops->stats();
	if (rtcv_snap == rcu_torture_current_version &&
	    rcu_torture_current != NULL) {
		int __maybe_unused flags;
		unsigned long __maybe_unused gpnum;
		unsigned long __maybe_unused completed;

		rcutorture_get_gp_data(cur_ops->ttype,
				       &flags, &gpnum, &completed);
		pr_alert("??? Writer stall state %d g%lu c%lu f%#x\n",
			 rcu_torture_writer_state,
			 gpnum, completed, flags);
		show_rcu_gp_kthreads();
		rcutorture_trace_dump();
	}
	rtcv_snap = rcu_torture_current_version;
}
