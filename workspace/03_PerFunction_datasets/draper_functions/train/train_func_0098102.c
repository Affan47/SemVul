thin_presuspend(struct dm_target *ti)
{
	struct thin_c *tc = ti->private;

	if (dm_noflush_suspending(ti))
		noflush_work(tc, do_noflush_start);
}
