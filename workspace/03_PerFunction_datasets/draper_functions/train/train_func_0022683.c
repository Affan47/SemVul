gw_settings_search_field_new ( void)
{
	GWSettingsSearchField *p = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (p = (GWSettingsSearchField*)g_malloc ( sizeof ( GWSettingsSearchField))) != NULL )
	{
		p->name = NULL;
		p->position = -1;
		p->position_v = NULL;
		p->visible = FALSE;
		p->visible_v = NULL;
	}

	return p;
}
