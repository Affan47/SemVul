poll_logical_volume(struct cmd_context *cmd, struct logical_volume *lv,
			       int wait_completion)
{
	struct lvinfo info;

	if (!lv_info(cmd, lv, 0, &info, 0, 0) || !info.exists) {
		log_print_unless_silent("Conversion starts after activation.");
		return ECMD_PROCESSED;
	}
	return lvconvert_poll(cmd, lv, wait_completion ? 0 : 1U);
}
