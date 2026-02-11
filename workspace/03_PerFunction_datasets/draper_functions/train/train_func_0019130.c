rssyl_done(void)
{
	prefs_toolbar_unregister_plugin_item(TOOLBAR_MAIN, "RSSyl",
			_("Refresh all feeds"));
	rssyl_prefs_done();
	rssyl_gtk_done();
	if (!claws_is_exiting())
		folder_unregister_class(rssyl_folder_get_class());
}
