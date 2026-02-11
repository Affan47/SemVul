stats_dump_pools_to_buffer(struct stream_interface *si)
{
	dump_pools_to_trash();
	if (bi_putchk(si->ib, &trash) == -1)
		return 0;
	return 1;
}
