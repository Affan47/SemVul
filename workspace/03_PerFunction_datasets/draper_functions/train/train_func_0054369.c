reset()
{
	delete stream;
	stream = 0;

	delete tls;
	tls = 0;
	tlsHandler = 0;

	delete conn;
	conn = 0;
}
