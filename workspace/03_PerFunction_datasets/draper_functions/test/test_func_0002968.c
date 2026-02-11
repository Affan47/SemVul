pnfs_layout_io_test_failed(struct pnfs_layout_hdr *lo, u32 iomode)
{
	unsigned long start, end;
	int fail_bit = pnfs_iomode_to_fail_bit(iomode);

	if (test_bit(fail_bit, &lo->plh_flags) == 0)
		return false;
	end = jiffies;
	start = end - PNFS_LAYOUTGET_RETRY_TIMEOUT;
	if (!time_in_range(lo->plh_retry_timestamp, start, end)) {

		pnfs_layout_clear_fail_bit(lo, fail_bit);
		return false;
	}
	return true;
}
