o2hb_region_blocks_store(struct config_item *item,
					const char *page,
					size_t count)
{
	struct o2hb_region *reg = to_o2hb_region(item);
	unsigned long tmp;
	char *p = (char *)page;

	if (reg->hr_bdev)
		return -EINVAL;

	tmp = simple_strtoul(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		return -EINVAL;

	if (tmp > O2NM_MAX_NODES || tmp == 0)
		return -ERANGE;

	reg->hr_blocks = (unsigned int)tmp;

	return count;
}
