LogCheckpointEnd(bool restartpoint)
{
	long		write_secs,
				sync_secs,
				total_secs,
				longest_secs,
				average_secs;
	int			write_usecs,
				sync_usecs,
				total_usecs,
				longest_usecs,
				average_usecs;
	uint64		average_sync_time;

	CheckpointStats.ckpt_end_t = GetCurrentTimestamp();

	TimestampDifference(CheckpointStats.ckpt_start_t,
						CheckpointStats.ckpt_end_t,
						&total_secs, &total_usecs);

	TimestampDifference(CheckpointStats.ckpt_write_t,
						CheckpointStats.ckpt_sync_t,
						&write_secs, &write_usecs);

	TimestampDifference(CheckpointStats.ckpt_sync_t,
						CheckpointStats.ckpt_sync_end_t,
						&sync_secs, &sync_usecs);


	longest_secs = (long) (CheckpointStats.ckpt_longest_sync / 1000000);
	longest_usecs = CheckpointStats.ckpt_longest_sync -
		(uint64) longest_secs *1000000;

	average_sync_time = 0;
	if (CheckpointStats.ckpt_sync_rels > 0)
		average_sync_time = CheckpointStats.ckpt_agg_sync_time /
			CheckpointStats.ckpt_sync_rels;
	average_secs = (long) (average_sync_time / 1000000);
	average_usecs = average_sync_time - (uint64) average_secs *1000000;

	if (restartpoint)
		elog(LOG, "restartpoint complete: wrote %d buffers (%.1f%%); "
			 "%d transaction log file(s) added, %d removed, %d recycled; "
			 "write=%ld.%03d s, sync=%ld.%03d s, total=%ld.%03d s; "
			 "sync files=%d, longest=%ld.%03d s, average=%ld.%03d s",
			 CheckpointStats.ckpt_bufs_written,
			 (double) CheckpointStats.ckpt_bufs_written * 100 / NBuffers,
			 CheckpointStats.ckpt_segs_added,
			 CheckpointStats.ckpt_segs_removed,
			 CheckpointStats.ckpt_segs_recycled,
			 write_secs, write_usecs / 1000,
			 sync_secs, sync_usecs / 1000,
			 total_secs, total_usecs / 1000,
			 CheckpointStats.ckpt_sync_rels,
			 longest_secs, longest_usecs / 1000,
			 average_secs, average_usecs / 1000);
	else
		elog(LOG, "checkpoint complete: wrote %d buffers (%.1f%%); "
			 "%d transaction log file(s) added, %d removed, %d recycled; "
			 "write=%ld.%03d s, sync=%ld.%03d s, total=%ld.%03d s; "
			 "sync files=%d, longest=%ld.%03d s, average=%ld.%03d s",
			 CheckpointStats.ckpt_bufs_written,
			 (double) CheckpointStats.ckpt_bufs_written * 100 / NBuffers,
			 CheckpointStats.ckpt_segs_added,
			 CheckpointStats.ckpt_segs_removed,
			 CheckpointStats.ckpt_segs_recycled,
			 write_secs, write_usecs / 1000,
			 sync_secs, sync_usecs / 1000,
			 total_secs, total_usecs / 1000,
			 CheckpointStats.ckpt_sync_rels,
			 longest_secs, longest_usecs / 1000,
			 average_secs, average_usecs / 1000);
}
