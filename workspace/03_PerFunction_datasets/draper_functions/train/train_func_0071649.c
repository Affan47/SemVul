set_transfer_voltage_high(int val) {
	char response[MAX_RESPONSE_LENGTH];
	char *ptr;
	int low;

	if (do_command(POLL, TRANSFER_VOLTAGE, "", response) <= 0)
		return;
	ptr = field(response, 0);
	if (!ptr)
		return;
	low = atoi(ptr);
	ptr = field(response, 1);
	if (!ptr || val == atoi(ptr))
		return;
	snprintf(response, sizeof(response), "%d;%d", low, val);
	do_command(SET, TRANSFER_VOLTAGE, response, NULL);
}
