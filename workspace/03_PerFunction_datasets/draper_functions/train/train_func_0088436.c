job_scan_major_mod_union_card_table (void *worker_data_untyped, SgenThreadPoolJob *job)
{
	WorkerData *worker_data = (WorkerData *)worker_data_untyped;
	ScanJob *job_data = (ScanJob*)job;
	ScanCopyContext ctx = CONTEXT_FROM_OBJECT_OPERATIONS (job_data->ops, sgen_workers_get_job_gray_queue (worker_data));

	g_assert (concurrent_collection_in_progress);
	major_collector.scan_card_table (TRUE, ctx);
}
