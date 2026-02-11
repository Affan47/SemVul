monitor_final_summary()
{
	decode_zombie_status(summary, first_process_sigchild_status);

	summary->end       = usecs_since_epoch();
	summary->wall_time = summary->end - summary->start;

	if(log_summary)
		rmsummary_print(log_summary, summary);

	if(log_opened)
		monitor_file_io_summaries();

	if(summary->limits_exceeded && summary->exit_status == 0)
		return -1;
	else
		return summary->exit_status;
}
