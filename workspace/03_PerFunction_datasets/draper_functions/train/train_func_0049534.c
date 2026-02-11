plugin_done (void)
{
	if (NewLog) {
		(void)fclose (NewLog);
		NewLog  = NULL;
	}
	if (LogName) {
		g_free(LogName);
		LogName = NULL;
	}
	if (pluginDesc) {
		g_free(pluginDesc);
		pluginDesc = NULL;
	}
	hooks_unregister_hook (MAIL_POSTFILTERING_HOOKLIST, hook_id);

	debug_print ("Newmail plugin unloaded\n");
	return TRUE;
}
