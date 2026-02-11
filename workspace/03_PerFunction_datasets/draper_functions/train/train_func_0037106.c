comp_write_worker(u64 lba, u32 num, const u8 *arr)
{
	bool res;
	u64 block, rest = 0;
	u32 store_blks = sdebug_store_sectors;
	u32 lb_size = scsi_debug_sector_size;

	block = do_div(lba, store_blks);
	if (block + num > store_blks)
		rest = block + num - store_blks;

	res = !memcmp(fake_storep + (block * lb_size), arr,
		      (num - rest) * lb_size);
	if (!res)
		return res;
	if (rest)
		res = memcmp(fake_storep, arr + ((num - rest) * lb_size),
			     rest * lb_size);
	if (!res)
		return res;
	arr += num * lb_size;
	memcpy(fake_storep + (block * lb_size), arr, (num - rest) * lb_size);
	if (rest)
		memcpy(fake_storep, arr + ((num - rest) * lb_size),
		       rest * lb_size);
	return res;
}
