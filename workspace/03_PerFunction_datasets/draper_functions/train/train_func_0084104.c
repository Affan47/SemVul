SetTime(const TRemoteInfo &ri, const THarmonyTime &ht,
	lc_callback cb, void *cb_arg, uint32_t cb_stage)
{
	int err = 0;
	uint8_t rsp[68];
	int cb_count = 0;

	if (cb)
		cb(cb_stage, cb_count++, 0, 2, LC_CB_COUNTER_TYPE_STEPS, cb_arg,
			NULL);

	if (ri.architecture < 8) {
		uint8_t tsv[8];
		tsv[0] = 0;
		tsv[1] = ht.minute;
		tsv[2] = ht.hour;
		tsv[3] = ht.day - 1;
		tsv[4] = ht.month  -1;
		tsv[5] = ht.year - 2000;
		if ((err = WriteMiscByte(0, 6, COMMAND_MISC_STATE, tsv)))
			return err;
		if (cb)
			cb(cb_stage, cb_count++, 1, 3, LC_CB_COUNTER_TYPE_STEPS,
				cb_arg, NULL);

		tsv[0] = ht.second;
		err = WriteMiscByte(0, 1, COMMAND_MISC_STATE, tsv);
	} else {
		uint16_t tsv[8];
		tsv[0] = 0;
		tsv[1] = ht.minute;
		tsv[2] = ht.hour;
		tsv[3] = ht.day-1;
		tsv[4] = ht.dow;
		tsv[5] = ht.month-1;
		tsv[6] = ht.year-2000;
		if ((err = WriteMiscWord(0, 7, COMMAND_MISC_STATE, tsv)))
			return err;
		if (cb)
			cb(cb_stage, cb_count++, 1, 3, LC_CB_COUNTER_TYPE_STEPS,
				cb_arg, NULL);
		tsv[0] = ht.second;
		if ((err = WriteMiscWord(0, 1, COMMAND_MISC_STATE, tsv)))
			return err;


		if (ri.architecture == 8) {
			static const uint8_t rcc[64] = {
				COMMAND_WRITE_MISC | 0x01,
				COMMAND_MISC_CLOCK_RECALCULATE };
			err = HID_WriteReport(rcc);
		}
	}
	if (cb)
		cb(cb_stage, cb_count++, 2, 3, LC_CB_COUNTER_TYPE_STEPS, cb_arg,
			NULL);

        if (err != 0) {
		return err;
	}


	err = HID_ReadReport(rsp);
	if (err == 0) {
		if ((rsp[0] & COMMAND_MASK) != RESPONSE_DONE) {
			err = 1;
		}
	} else {
		err = 0;
	}
	if (cb)
		cb(cb_stage, cb_count++, 3, 3, LC_CB_COUNTER_TYPE_STEPS, cb_arg,
			NULL);

	return err;
}
