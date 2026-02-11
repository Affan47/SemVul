LearnIR(uint32_t *freq, uint32_t **ir_signal,
		uint32_t *ir_signal_length, lc_callback cb, void *cb_arg,
		uint32_t cb_stage)
{
	int err = 0;
	uint32_t cb_count = 0;

	const uint8_t msg_one[MH_MAX_PACKET_SIZE] =
		{ 0xFF, 0x01, 0x00, 0x02, 0x80, '/', 'i', 'r', '/', 'i', 'r',
		  '_', 'c', 'a', 'p', 0x00, 0x80, 'R', 0x00 };
	const uint8_t msg_two[MH_MAX_PACKET_SIZE] =
		{ 0xFF, 0x04, 0x01, 0x02, 0x01, 0x0C, 0x01, 0x00 };
	uint8_t rsp[MH_MAX_PACKET_SIZE];

	if (cb) {
		cb(cb_stage, 0, 0, 1, LC_CB_COUNTER_TYPE_STEPS, cb_arg, NULL);
	}

	if ((err = HID_WriteReport(msg_one))) {
		debug("Failed to write to remote");
		return LC_ERROR_WRITE;
	}
	if ((err = HID_ReadReport(rsp))) {
		debug("Failed to read from remote");
		return LC_ERROR_READ;
	}
	debug("msg_one");
	debug_print_packet(rsp);

	if ((err = HID_WriteReport(msg_two))) {
		debug("Failed to write to remote");
		return LC_ERROR_WRITE;
	}
	if ((err = HID_ReadReport(rsp))) {
		debug("Failed to read from remote");
		return LC_ERROR_READ;
	}
	debug("msg_two");
	debug_print_packet(rsp);

	err = LearnIRInnerLoop(freq, ir_signal, ir_signal_length, 0x90);


	const uint8_t msg_stop[MH_MAX_PACKET_SIZE] =
		{ 0xFF, 0x06, 0x02, 0x02, 0x01, 0x0C, 0x01, 0x06 };
	if (HID_WriteReport(msg_stop) != 0) {
		debug("Failed to write to remote");
		err = LC_ERROR_WRITE;
	}
	if (HID_ReadReport(rsp) != 0) {
		debug("Failed to read from remote");
		err = LC_ERROR_READ;
	}
	debug("msg_stop");
	debug_print_packet(rsp);


	const uint8_t msg_reset_seq[MH_MAX_PACKET_SIZE] =
		{ 0xFF, 0x07, 0x03, 0x01, 0x01, 0x0C };
	if (HID_WriteReport(msg_reset_seq) != 0) {
		debug("Failed to write to remote");
		err = LC_ERROR_WRITE;
	}
	if (HID_ReadReport(rsp) != 0) {
		debug("Failed to read from remote");
		err = LC_ERROR_READ;
	}
	debug("msg_reset_seq");
	debug_print_packet(rsp);

	if (cb && !err) {
		cb(cb_stage, 1, 1, 1, LC_CB_COUNTER_TYPE_STEPS, cb_arg, NULL);
	}

	return err;
}
