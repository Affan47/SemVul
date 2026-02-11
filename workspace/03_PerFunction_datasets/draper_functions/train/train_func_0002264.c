client_process(int fd, short events)
{
	struct mux_client *client = NULL;
	FOREACH(struct mux_client *lc, &client_list) {
		if(lc->fd == fd) {
			client = lc;
			break;
		}
	} ENDFOREACH

	if(!client) {
		usbmuxd_log(LL_ERROR, "client_process: fd %d not found in client list", fd);
		return;
	}

	if(client->state == CLIENT_CONNECTED) {
		usbmuxd_log(LL_SPEW, "client_process in CONNECTED state");
		device_client_process(client->connect_device, client, events);
	} else {
		if(events & POLLIN) {
			process_recv(client);
		} else if(events & POLLOUT) {
			process_send(client);
		}
	}

}
