factory(Scheduler& scheduler,FD accept_fd) {
	Cleanup<HttpServerConnection,CleanupClose> client(new HelloWorld(scheduler,accept_fd));
	client->construct();
	client.detach();
}
