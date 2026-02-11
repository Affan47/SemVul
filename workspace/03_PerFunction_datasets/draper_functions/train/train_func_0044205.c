wlcore_set_partition(struct wl1271 *wl,
			 const struct wlcore_partition_set *p)
{
	int ret;


	memcpy(&wl->curr_part, p, sizeof(*p));

	wl1271_debug(DEBUG_IO, "mem_start %08X mem_size %08X",
		     p->mem.start, p->mem.size);
	wl1271_debug(DEBUG_IO, "reg_start %08X reg_size %08X",
		     p->reg.start, p->reg.size);
	wl1271_debug(DEBUG_IO, "mem2_start %08X mem2_size %08X",
		     p->mem2.start, p->mem2.size);
	wl1271_debug(DEBUG_IO, "mem3_start %08X mem3_size %08X",
		     p->mem3.start, p->mem3.size);

	ret = wlcore_raw_write32(wl, HW_PART0_START_ADDR, p->mem.start);
	if (ret < 0)
		goto out;

	ret = wlcore_raw_write32(wl, HW_PART0_SIZE_ADDR, p->mem.size);
	if (ret < 0)
		goto out;

	ret = wlcore_raw_write32(wl, HW_PART1_START_ADDR, p->reg.start);
	if (ret < 0)
		goto out;

	ret = wlcore_raw_write32(wl, HW_PART1_SIZE_ADDR, p->reg.size);
	if (ret < 0)
		goto out;

	ret = wlcore_raw_write32(wl, HW_PART2_START_ADDR, p->mem2.start);
	if (ret < 0)
		goto out;

	ret = wlcore_raw_write32(wl, HW_PART2_SIZE_ADDR, p->mem2.size);
	if (ret < 0)
		goto out;


	ret = wlcore_raw_write32(wl, HW_PART3_START_ADDR, p->mem3.start);

out:
	return ret;
}
