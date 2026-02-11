remote_server_subscribe(RemoteConnection *rc, RemoteReadFunc *func, gpointer data)
{
	if (!rc || !rc->server) return;

	rc->read_func = func;
	rc->read_data = data;
}
