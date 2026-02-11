jack_transport_reposition (jack_client_t *client, const jack_position_t *pos)
{

	jack_position_t tmp = *pos;


	if (tmp.valid & ~JACK_POSITION_MASK)
		return EINVAL;

	return jack_transport_request_new_pos (client, &tmp);
}
