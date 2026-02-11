walk_system_ram_res(u64 start, u64 end, void *arg,
				int (*func)(u64, u64, void *))
{
	struct resource res;
	u64 orig_end;
	int ret = -1;

	res.start = start;
	res.end = end;
	res.flags = IORESOURCE_MEM | IORESOURCE_BUSY;
	orig_end = res.end;
	while ((res.start < res.end) &&
		(!find_next_iomem_res(&res, "System RAM", true))) {
		ret = (*func)(res.start, res.end, arg);
		if (ret)
			break;
		res.start = res.end + 1;
		res.end = orig_end;
	}
	return ret;
}
