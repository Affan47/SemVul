gsql_engine_menu_set_status (GSQLEngine *engine,
								gboolean status)
{
	GSQL_TRACE_FUNC;

	g_object_set(G_OBJECT(engine->action), "visible", status, NULL);
}
