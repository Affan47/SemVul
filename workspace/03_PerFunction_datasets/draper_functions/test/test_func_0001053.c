phonet_open(struct gn_statemachine *state)
{
	int result, i, n, total = 0;
	unsigned char init_sequence[] = { FBUS_PHONET_BLUETOOTH_FRAME_ID,
					  FBUS_DEVICE_PHONE,
					  FBUS_PHONET_BLUETOOTH_DEVICE_PC,
					  FBUS_PHONET_BLUETOOTH_INITSEQ,
					  0x04};
	unsigned char init_resp[7];
	unsigned char init_pattern[7] = { FBUS_PHONET_BLUETOOTH_FRAME_ID,
					 FBUS_PHONET_BLUETOOTH_DEVICE_PC,
					 FBUS_DEVICE_PHONE,
					 FBUS_PHONET_BLUETOOTH_INITSEQ,
					 0x05};

	if (!state)
		return false;

	memset(&init_resp, 0, 7);


	result = device_open(state->config.port_device, false, false, false,
			     state->config.connection_type, state);

	if (!result) {
		perror(_("Couldn't open PHONET device"));
		return false;
	}

	if (state->config.connection_type == GN_CT_Bluetooth) {
		device_write(&init_sequence, 7, state);
		while (total < 7) {
			n = device_read(&init_resp + total, 7 - total, state);
			if (n > 0)
				total += n;
		}
		for (i = 0; i < n; i++) {
			if (init_resp[i] != init_pattern[i]) {
				dprintf("Incorrect byte in the answer\n");
				return false;
			}
		}
	}

	return true;
}
