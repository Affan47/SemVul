process (jack_nframes_t nframes, void* arg)
{
	jack_client_t* client = (jack_client_t*) arg;

	while ((nframes = jack_thread_wait (client, _process (nframes))) != 0);

	return 0;
}
