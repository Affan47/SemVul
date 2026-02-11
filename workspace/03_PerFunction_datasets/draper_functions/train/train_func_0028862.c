more_bytes()
{
	if (peer->type == HTTP_CLIENT)
		return more_client_bytes();

	return more_server_bytes();
}
