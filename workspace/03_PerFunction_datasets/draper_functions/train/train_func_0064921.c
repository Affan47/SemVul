reset_stats(int level)
{
	slurmctld_diag_stats.proc_req_raw = 0;
	slurmctld_diag_stats.proc_req_threads = 0;
	slurmctld_diag_stats.schedule_cycle_max = 0;
	slurmctld_diag_stats.schedule_cycle_sum = 0;
	slurmctld_diag_stats.schedule_cycle_counter = 0;
	slurmctld_diag_stats.schedule_cycle_depth = 0;
	slurmctld_diag_stats.jobs_submitted = 0;
	slurmctld_diag_stats.jobs_started = 0;
	slurmctld_diag_stats.jobs_completed = 0;
	slurmctld_diag_stats.jobs_canceled = 0;
	slurmctld_diag_stats.jobs_failed = 0;


	if (level)
		slurmctld_diag_stats.backfilled_jobs = 0;

	slurmctld_diag_stats.last_backfilled_jobs = 0;
	slurmctld_diag_stats.bf_cycle_counter = 0;
	slurmctld_diag_stats.bf_cycle_sum = 0;
	slurmctld_diag_stats.bf_cycle_last = 0;
	slurmctld_diag_stats.bf_depth_sum = 0;
	slurmctld_diag_stats.bf_depth_try_sum = 0;
	slurmctld_diag_stats.bf_queue_len = 0;
	slurmctld_diag_stats.bf_queue_len_sum = 0;
	slurmctld_diag_stats.bf_cycle_max = 0;
	slurmctld_diag_stats.bf_last_depth = 0;
	slurmctld_diag_stats.bf_last_depth_try = 0;
	slurmctld_diag_stats.bf_active = 0;
}
