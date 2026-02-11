cper_next_record_id(void)
{
	static atomic64_t seq;

	if (!atomic64_read(&seq))
		atomic64_set(&seq, ((u64)get_seconds()) << 32);

	return atomic64_inc_return(&seq);
}
