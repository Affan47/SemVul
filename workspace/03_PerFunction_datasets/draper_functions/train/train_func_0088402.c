shell_timer(time_t now)
{
	time_delta_t timeout = GNET_PROPERTY(remote_shell_timeout);

	if (timeout > 0) {
		GSList *sl, *to_remove = NULL;

		for (sl = sl_shells; sl != NULL; sl = g_slist_next(sl)) {
			struct gnutella_shell *sh = sl->data;

			shell_check(sh);
			if (
				0 == (SOCK_F_LOCAL & sh->socket->flags) &&
				delta_time(now, sh->last_update) > timeout
			) {
				to_remove = g_slist_prepend(to_remove, sh);
			}
		}
		for (sl = to_remove; sl != NULL; sl = g_slist_next(sl)) {
			struct gnutella_shell *sh = sl->data;
			shell_destroy(sh);
		}
		g_slist_free(to_remove);
	}
}
