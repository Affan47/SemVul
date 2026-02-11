setup_client (jack_engine_t *engine, ClientType type, char *name, jack_client_id_t uuid,
	      jack_options_t options, jack_status_t *status, int client_fd,
	      const char *object_path, const char *object_data)
{

	jack_client_internal_t *client;


	if (jack_client_name_invalid (engine, name, options, status))
		return NULL;

	if (uuid != 0)
		jack_ensure_uuid_unique (engine, uuid);


	if ((client = jack_setup_client_control (engine, client_fd,
						 type, name, uuid )) == NULL) {
		*status |= (JackFailure|JackInitFailure);
		jack_error ("cannot create new client object");
		return NULL;
	}


	if (type == ClientInternal) {
		if (jack_load_client (engine, client, object_path)) {
			jack_error ("cannot dynamically load client from"
				    " \"%s\"", object_path);
			jack_client_delete (engine, client);
			*status |= (JackFailure|JackLoadFailure);
			return NULL;
		}
	}

	VERBOSE (engine, "new client: %s, id = %" PRIu32
		 " type %d @ %p fd = %d",
		 client->control->name, client->control->id,
		 type, client->control, client_fd);

	if (jack_client_is_internal(client)) {


		client->private_client =
			jack_client_alloc_internal (client->control, engine);


		client->private_client->deliver_request = internal_client_request;
		client->private_client->deliver_arg = engine;
	}


	jack_lock_graph (engine);
 	engine->clients = jack_slist_prepend (engine->clients, client);
	jack_engine_reset_rolling_usecs (engine);

	if (jack_client_is_internal(client)) {


		jack_unlock_graph (engine);


		if (client->control->type == ClientInternal) {

			pthread_mutex_unlock (&engine->request_lock);
			if (client->initialize (client->private_client,
						object_data)) {


				VERBOSE (engine,
					 "%s jack_initialize() failed!",
					 client->control->name);
				jack_lock_graph (engine);
				jack_remove_client (engine, client);
				jack_unlock_graph (engine);
				*status |= (JackFailure|JackInitFailure);
				client = NULL;


			}
			pthread_mutex_lock (&engine->request_lock);
		}

	} else {

		jack_unlock_graph (engine);
	}

	return client;
}
