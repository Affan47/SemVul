nemo_search_engine_simple_stop (NemoSearchEngine *engine)
{
	NemoSearchEngineSimple *simple;

	simple = NEMO_SEARCH_ENGINE_SIMPLE (engine);

	if (simple->details->active_search != NULL) {
		g_cancellable_cancel (simple->details->active_search->cancellable);
		simple->details->active_search = NULL;
	}
}
