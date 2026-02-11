FinishConfig(const TRemoteInfo &ri, lc_callback cb, void *cb_arg,
        uint32_t cb_stage)
{
	int err;
	uint8_t data_one[1]  = { 0x01 };
	uint8_t data_zero[1] = { 0x00 };

	if (ri.architecture != 14) {
		return 0;
	}

	if (cb)
		cb(cb_stage, 0, 0, 2, LC_CB_COUNTER_TYPE_STEPS, cb_arg, NULL);

	if ((err = WriteMiscByte(0x03, 1, COMMAND_MISC_RESTART_CONFIG, data_one))) {
		return err;
	}

	if (cb)
		cb(cb_stage, 1, 1, 2, LC_CB_COUNTER_TYPE_STEPS, cb_arg, NULL);

	if ((err = WriteMiscByte(0x06, 1, COMMAND_MISC_RESTART_CONFIG, data_zero))) {
		return err;
	}

	if (cb)
		cb(cb_stage, 2, 2, 2, LC_CB_COUNTER_TYPE_STEPS, cb_arg, NULL);

	return 0;
}
