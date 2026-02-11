update_region(struct vc_data *vc, unsigned long start, int count)
{
	WARN_CONSOLE_UNLOCKED();

	if (DO_UPDATE(vc)) {
		hide_cursor(vc);
		do_update_region(vc, start, count);
		set_cursor(vc);
	}
}
