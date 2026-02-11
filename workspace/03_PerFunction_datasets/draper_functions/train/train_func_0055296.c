unlock_notify_changes (void)
{
	if (user_notify_changes != 0)
		g_signal_handler_unblock (mon_conf_user, user_notify_changes);
	if (global_notify_changes != 0)
		g_signal_handler_unblock (mon_conf_global, global_notify_changes);
}
