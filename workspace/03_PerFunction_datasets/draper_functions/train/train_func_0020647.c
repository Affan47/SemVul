process_ded_retry(struct mem_ctl_info *mci, u16 error,
				u32 retry_add, int *error_found,
				int handle_error)
{
	*error_found = 1;

	if (handle_error)
		do_process_ded_retry(mci, error, retry_add);
}
