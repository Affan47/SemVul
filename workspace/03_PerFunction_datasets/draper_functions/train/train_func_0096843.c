client_discard_input(struct client *client)
{
	if (http_conn_current_message_has_body(client->conn)) {
		log_debug("proxy: will discard client msg body");
		http_conn_disable_persistence(client->conn);
		client->state = CLIENT_STATE_DISCARD_INPUT;
	}
}
