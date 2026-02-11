fs_unlock(void)
{
	if (!critical_section()) {
		log_debug("Syncing device names");

		if (!dm_udev_wait(_fs_cookie))
			stack;
		_fs_cookie = DM_COOKIE_AUTO_CREATE;
		dm_lib_release();
		_pop_fs_ops();
	}
}
