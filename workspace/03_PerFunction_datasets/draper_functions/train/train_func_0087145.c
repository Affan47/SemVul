process_recv(struct mux_client *client)
{
	int res;
	int did_read = 0;
	if(client->ib_size < sizeof(struct client_header)) {
		res = recv(client->fd, client->ib_buf + client->ib_size, sizeof(struct client_header) - client->ib_size, 0);
		if(res <= 0) {
			if(res < 0)
				usbmuxd_log(LL_ERROR, "Receive from client fd %d failed: %s", client->fd, strerror(errno));
			else
				usbmuxd_log(LL_INFO, "Client %d connection closed", client->fd);
			client_close(client);
			return;
		}
		client->ib_size += res;
		if(client->ib_size < sizeof(struct client_header))
			return;
		did_read = 1;
	}
	struct client_header *hdr = (void*)client->ib_buf;
	if(hdr->version != CLIENT_PROTOCOL_VERSION) {
		usbmuxd_log(LL_INFO, "Client %d version mismatch: expected %d, got %d", client->fd, CLIENT_PROTOCOL_VERSION, hdr->version);
		client_close(client);
	}
	if(hdr->length > client->ib_capacity) {
		usbmuxd_log(LL_INFO, "Client %d message is too long (%d bytes)", client->fd, hdr->length);
		client_close(client);
	}
	if(hdr->length < sizeof(struct client_header)) {
		usbmuxd_log(LL_ERROR, "Client %d message is too short (%d bytes)", client->fd, hdr->length);
		client_close(client);
	}
	if(client->ib_size < hdr->length) {
		if(did_read)
			return;
		res = recv(client->fd, client->ib_buf + client->ib_size, hdr->length - client->ib_size, 0);
		if(res < 0) {
			usbmuxd_log(LL_ERROR, "Receive from client fd %d failed: %s", client->fd, strerror(errno));
			client_close(client);
			return;
		} else if(res == 0) {
			usbmuxd_log(LL_INFO, "Client %d connection closed", client->fd);
			client_close(client);
			return;
		}
		client->ib_size += res;
		if(client->ib_size < hdr->length)
			return;
	}
	client_command(client, hdr, (char *)(hdr+1));
	client->ib_size = 0;
}
