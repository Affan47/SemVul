gb_debug_init (void)
{
	if (g_getenv ("GBONDS_DEBUG") != NULL)
	{

		debug_flags = ~GBONDS_DEBUG_NONE;
		return;
	}

	if (g_getenv ("GBONDS_DEBUG_VIEW") != NULL)
		debug_flags |= GBONDS_DEBUG_VIEW;
	if (g_getenv ("GBONDS_DEBUG_PRINT") != NULL)
		debug_flags |= GBONDS_DEBUG_PRINT;
	if (g_getenv ("GBONDS_DEBUG_PREFS") != NULL)
		debug_flags |= GBONDS_DEBUG_PREFS;
	if (g_getenv ("GBONDS_DEBUG_FILE") != NULL)
		debug_flags |= GBONDS_DEBUG_FILE;
	if (g_getenv ("GBONDS_DEBUG_DOC") != NULL)
		debug_flags |= GBONDS_DEBUG_DOC;
	if (g_getenv ("GBONDS_DEBUG_XML") != NULL)
		debug_flags |= GBONDS_DEBUG_XML;
	if (g_getenv ("GBONDS_DEBUG_TABLE") != NULL)
		debug_flags |= GBONDS_DEBUG_TABLE;
	if (g_getenv ("GBONDS_DEBUG_UPDATE") != NULL)
		debug_flags |= GBONDS_DEBUG_UPDATE;
	if (g_getenv ("GBONDS_DEBUG_UNDO") != NULL)
		debug_flags |= GBONDS_DEBUG_UNDO;
	if (g_getenv ("GBONDS_DEBUG_RECENT") != NULL)
		debug_flags |= GBONDS_DEBUG_RECENT;
	if (g_getenv ("GBONDS_DEBUG_COMMANDS") != NULL)
		debug_flags |= GBONDS_DEBUG_COMMANDS;
	if (g_getenv ("GBONDS_DEBUG_WINDOW") != NULL)
		debug_flags |= GBONDS_DEBUG_WINDOW;
	if (g_getenv ("GBONDS_DEBUG_UI") != NULL)
		debug_flags |= GBONDS_DEBUG_UI;
}
