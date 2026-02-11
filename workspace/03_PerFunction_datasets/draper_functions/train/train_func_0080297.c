user_quick_search_new ( void)
{
	struct user_quick_search *p = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( (p = ( struct user_quick_search*)g_malloc0 ( sizeof ( struct user_quick_search))) != NULL)
	{
		p->quick_search = engine_quick_search_new ( );
		p->search_type = 0;
	}

	return p;
}
