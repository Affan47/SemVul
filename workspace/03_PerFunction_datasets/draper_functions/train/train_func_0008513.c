jack_do_reserve_name ( jack_engine_t *engine, jack_request_t *req)
{
	jack_reserved_name_t *reservation;
	JSList *node;

	for (node = engine->clients; node; node = jack_slist_next (node)) {
		jack_client_internal_t* client = (jack_client_internal_t*) node->data;
		if( !strcmp( (char *)client->control->name, req->x.reservename.name )) {
			req->status = -1;
			return;
		}
	}

	reservation = malloc( sizeof( jack_reserved_name_t ) );
	if( reservation == NULL ) {
		req->status = -1;
		return;
	}

	snprintf( reservation->name, sizeof( reservation->name ), "%s", req->x.reservename.name );
	reservation->uuid = req->x.reservename.uuid;
	engine->reserved_client_names = jack_slist_append( engine->reserved_client_names, reservation );

	req->status = 0;
}
