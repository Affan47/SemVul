cu_two_completed (SoupSession *session, SoupMessage *msg, gpointer loop)
{
	debug_printf (2, "  Message 2 completed\n");
	if (msg->status_code != SOUP_STATUS_CANT_CONNECT) {
		debug_printf (1, "  Unexpected status on Message 2: %d %s\n",
			      msg->status_code, msg->reason_phrase);
		errors++;
	}
	g_idle_add (cu_idle_quit, loop);
}
