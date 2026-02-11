irecv_reset_counters(irecv_client_t client) {
	if (check_context(client) != IRECV_E_SUCCESS) return IRECV_E_NO_DEVICE;
	if (client->mode == kDfuMode) {
		irecv_control_transfer(client, 0x21, 4, 0, 0, 0, 0, 1000);
	}
	return IRECV_E_SUCCESS;
}
