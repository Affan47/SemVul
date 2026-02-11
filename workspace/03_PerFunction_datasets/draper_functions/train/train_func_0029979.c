jack_engine_freewheel (void *arg)
{
	jack_engine_t* engine = (jack_engine_t *) arg;
	jack_client_internal_t* client;

	VERBOSE (engine, "freewheel thread starting ...");


	client = jack_client_internal_by_id (engine, engine->fwclient);

	while (!engine->stop_freewheeling) {

		jack_run_one_cycle (engine, engine->control->buffer_size, 0.0f);

		if (client && client->error) {


			break;
		}
	}

	VERBOSE (engine, "freewheel came to an end, naturally");
	return 0;
}
