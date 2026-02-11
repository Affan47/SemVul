jack_engine_reset_rolling_usecs (jack_engine_t *engine)
{
	memset (engine->rolling_client_usecs, 0,
		sizeof (engine->rolling_client_usecs));
	engine->rolling_client_usecs_index = 0;
	engine->rolling_client_usecs_cnt = 0;

	if (engine->driver) {
		engine->rolling_interval =
			jack_rolling_interval (engine->driver->period_usecs);
	} else {
		engine->rolling_interval = JACK_ENGINE_ROLLING_INTERVAL;
	}

	engine->spare_usecs = 0;
}
