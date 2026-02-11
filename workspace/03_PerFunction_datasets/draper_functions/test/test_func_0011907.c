handle_client() {
	if(!client_socket) return;

	string remote_addr;
	uint16_t remote_port = 0;
	try {
		remote_addr = client_socket->foreign_addr();
		remote_port = client_socket->foreign_port();
		Logger::log(remote_addr, remote_port, "connected", Logger::LOGLEVEL_INFO);
	}
	catch(const std::exception& e) {
		Logger::log( e.what() );
	}


	welcome();

	int received;
	char rx_buffer[BUFFERLENGTH];

	while( ( received = client_socket->receive(rx_buffer, BUFFERLENGTH) ) > 0 ) {
		Logger::log("MAVShell received", received, "bytes", Logger::LOGLEVEL_DEBUG);

		input_stream.write(rx_buffer, received);

		tokenize_stream(input_stream);
	}

	Logger::log(remote_addr, remote_port, "disconnected", Logger::LOGLEVEL_INFO);
	client_socket = NULL;
}
