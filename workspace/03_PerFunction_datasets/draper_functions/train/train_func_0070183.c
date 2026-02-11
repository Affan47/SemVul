on_debug_auto_run(G_GNUC_UNUSED GArray *nodes)
{
	if (debug_auto_run && !thread_count)
	{
		if (breaks_active())
			debug_send_command(N, "-exec-run");
		else
			dialogs_show_msgbox(GTK_MESSAGE_INFO, _("No breakpoints. Hanging."));
	}
}
