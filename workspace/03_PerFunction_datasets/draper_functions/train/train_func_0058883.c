scratch_inc_extra_ptr(int *ptr, int len)
{
	*ptr = (*ptr + len) % scratch_buf_size;

	PDEBUG(DBG_SCRATCH, "ptr=%d\n", *ptr);
}
