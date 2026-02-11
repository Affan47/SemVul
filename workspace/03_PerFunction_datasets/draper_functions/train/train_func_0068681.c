e_gdbus_templates_init_main_thread (void)
{
	if (!main_thread) {
		main_thread = g_thread_self ();
	} else if (main_thread != g_thread_self ()) {
		g_warning ("%s: Called in different main thread, stored: %p would use: %p", G_STRFUNC, main_thread, g_thread_self ());
	}
}
