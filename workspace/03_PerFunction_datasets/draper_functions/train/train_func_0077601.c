find_engine(const char *engine_name)
{
	struct ast_speech_engine *engine = NULL;


	if (ast_strlen_zero(engine_name))
		return default_engine;

	AST_RWLIST_RDLOCK(&engines);
	AST_RWLIST_TRAVERSE(&engines, engine, list) {
		if (!strcasecmp(engine->name, engine_name)) {
			break;
		}
	}
	AST_RWLIST_UNLOCK(&engines);

	return engine;
}
