int_engine_init(ENGINE *e)
	{
	if (!ENGINE_init(e))
		return 0;
	if (!initialized_engines)
		initialized_engines = sk_ENGINE_new_null();
	if (!initialized_engines || !sk_ENGINE_push(initialized_engines, e))
		{
		ENGINE_finish(e);
		return 0;
		}
	return 1;
	}
