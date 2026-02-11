snd_oxfw_stream_update_simplex(struct snd_oxfw *oxfw,
				    struct amdtp_stream *stream)
{
	struct cmp_connection *conn;

	if (stream == &oxfw->tx_stream)
		conn = &oxfw->out_conn;
	else
		conn = &oxfw->in_conn;

	if (cmp_connection_update(conn) < 0)
		stop_stream(oxfw, stream);
	else
		amdtp_stream_update(stream);
}
