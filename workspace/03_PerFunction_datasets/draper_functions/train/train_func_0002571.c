mem_cgroup_write(struct kernfs_open_file *of,
				char *buf, size_t nbytes, loff_t off)
{
	struct mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	unsigned long nr_pages;
	int ret;

	buf = strstrip(buf);
	ret = page_counter_memparse(buf, "-1", &nr_pages);
	if (ret)
		return ret;

	switch (MEMFILE_ATTR(of_cft(of)->private)) {
	case RES_LIMIT:
		if (mem_cgroup_is_root(memcg)) {
			ret = -EINVAL;
			break;
		}
		switch (MEMFILE_TYPE(of_cft(of)->private)) {
		case _MEM:
			ret = mem_cgroup_resize_limit(memcg, nr_pages);
			break;
		case _MEMSWAP:
			ret = mem_cgroup_resize_memsw_limit(memcg, nr_pages);
			break;
		case _KMEM:
			ret = memcg_update_kmem_limit(memcg, nr_pages);
			break;
		}
		break;
	case RES_SOFT_LIMIT:
		memcg->soft_limit = nr_pages;
		ret = 0;
		break;
	}
	return ret ?: nbytes;
}
