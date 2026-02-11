spotify_fsm (SPOTIFYSESSION * s)
{
	PHEADER hdr;
	unsigned char *payload;
	int ret;

#ifdef DEBUG
	printf ("spotify_fsm(): Entering with Spotify client %s in state %d\n", s->client_id, s->state);
#endif

	ret = 0;
	switch (s->state) {
	case CLIENT_STATE_IDLE_DISCONNECTED:
		break;

	case CLIENT_STATE_ALLOCATE:
		if ((s->session = session_init_client ()) == NULL) {
			s->state = CLIENT_STATE_ERROR_CONNECT;
			break;
		}

		s->state = CLIENT_STATE_CONNECT;

	case CLIENT_STATE_CONNECT:
		s->state = CLIENT_STATE_KEY_EXCHANGE;
		session_auth_set (s->session, s->username, s->password);
		if (session_connect (s->session)) {
			s->state = CLIENT_STATE_ERROR_CONNECT;
			break;
		}

	case CLIENT_STATE_KEY_EXCHANGE:
		s->state = CLIENT_STATE_AUTH;
		if (do_key_exchange (s->session)) {
			s->state = CLIENT_STATE_ERROR_KEY_EXCHANGE;
			break;
		}

	case CLIENT_STATE_AUTH:
		auth_generate_auth_hash (s->session);
		key_init (s->session);

		s->state = CLIENT_STATE_LOGIN_COMPLETE;
		if (do_auth (s->session)) {
			s->state = CLIENT_STATE_ERROR_AUTH;
		}
		break;

	case CLIENT_STATE_IDLE_CONNECTED:
		if (s->client_has_data) {
			s->client_has_data = 0;
			if ((ret =
			     packet_read (s->session, &hdr, &payload)) != 0) {
				s->state = CLIENT_STATE_ERROR_PACKET;
				break;
			}
			ret = handle_packet (s->session, hdr.cmd, payload,
					     hdr.len);
			free (payload);
			payload = NULL;
			if (ret != 0) {
				s->state = CLIENT_STATE_ERROR_PACKET;
				break;
			}

		}
		break;

	case CLIENT_STATE_LOGIN_COMPLETE:
	case CLIENT_STATE_COMMAND_COMPLETE:


		break;

	case CLIENT_STATE_ERROR_CONNECT:
	case CLIENT_STATE_ERROR_KEY_EXCHANGE:
	case CLIENT_STATE_ERROR_AUTH:
	case CLIENT_STATE_ERROR_PACKET:
	default:
		break;
	}

#ifdef DEBUG


	printf ("spotify_fsm(): Leaving with Spotify client %s in state %d\n",
		s->client_id, s->state);
#endif

	return ret;
}
