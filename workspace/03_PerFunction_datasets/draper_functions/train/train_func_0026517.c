r5_reserve_log_entry(struct r5l_log *log, struct r5l_io_unit *io)
{
	log->log_start = r5l_ring_add(log, log->log_start, BLOCK_SECTORS);


	if (log->log_start == 0)
		io->need_split_bio = true;

	io->log_end = log->log_start;
}
