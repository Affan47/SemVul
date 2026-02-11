expr_watch_new (AnjutaPlugin *plugin)
{
	ExprWatch *ew;

	ew = g_new0 (ExprWatch, 1);
	ew->plugin = plugin;
	create_expr_watch_gui (ew);
	ew->debugger = dma_debug_manager_get_queue (ANJUTA_PLUGIN_DEBUG_MANAGER (plugin));


	g_signal_connect (ew->plugin->shell, "save-session",
					  G_CALLBACK (on_session_save), ew);
    	g_signal_connect (ew->plugin->shell, "load-session",
					  G_CALLBACK (on_session_load), ew);


	anjuta_shell_add_widget (ew->plugin->shell,
							 ew->scrolledwindow,
                             "AnjutaDebuggerWatch", _("Watches"),
                             "gdb-watch-icon", ANJUTA_SHELL_PLACEMENT_BOTTOM,
                              NULL);


	g_signal_connect_swapped (ew->plugin, "program-started", G_CALLBACK (on_program_started), ew);

	return ew;
}
