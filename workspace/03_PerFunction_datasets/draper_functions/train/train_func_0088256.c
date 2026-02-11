gfire_close(gfire_data *p_gfire)
{
	if(!p_gfire)
		return;

	gfire_update_abort();

	PurpleConnection *gc = gfire_get_connection(p_gfire);


	if(p_gfire->userid)
	{
		if(gfire_preferences_get(p_gfire->prefs, 0x08) != purple_account_get_bool(purple_connection_get_account(gc), "show_fofs", TRUE))
		gfire_preferences_set(p_gfire->prefs, 0x08, purple_account_get_bool(purple_connection_get_account(gc), "show_fofs", TRUE));
			gfire_preferences_send(p_gfire->prefs, gc);
	}

	purple_debug(PURPLE_DEBUG_MISC, "gfire", "CONNECTION: close requested.\n");

	if(gc->inpa)
	{
		purple_debug(PURPLE_DEBUG_MISC, "gfire", "CONN: removing input handler\n");
		purple_input_remove(gc->inpa);
	}

#ifdef HAVE_GTK

	gfire_server_browser_free(p_gfire->server_browser);
#endif

	if(p_gfire->fd >= 0)
	{
		purple_debug(PURPLE_DEBUG_MISC, "gfire", "CONN: closing source file descriptor\n");
		close(p_gfire->fd);
		p_gfire->fd = -1;
	}

	gfire_free(p_gfire);

	gc->proto_data = NULL;
}
