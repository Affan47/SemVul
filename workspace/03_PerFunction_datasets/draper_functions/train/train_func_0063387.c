skip_free_areas_node(unsigned int flags, int nid)
{
	bool ret = false;
	unsigned int cpuset_mems_cookie;

	if (!(flags & SHOW_MEM_FILTER_NODES))
		goto out;

	do {
		cpuset_mems_cookie = read_mems_allowed_begin();
		ret = !node_isset(nid, cpuset_current_mems_allowed);
	} while (read_mems_allowed_retry(cpuset_mems_cookie));
out:
	return ret;
}
