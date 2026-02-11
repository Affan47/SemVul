SetTime(const TRemoteInfo &ri, const THarmonyTime &ht,
	lc_callback cb, void *cb_arg, uint32_t cb_stage)
{
	int err = 0;

	uint8_t tsv[16] = { ht.year, 0,
		ht.month,
		ht.day,
		ht.hour,
		ht.minute,
		ht.second,
		ht.dow,

		ht.utc_offset, 0,

		0, 0,
		0, 0,
		0, 0,

		};

	if ((err = Write(TYPE_REQUEST, COMMAND_UPDATE_TIME, 16, tsv))) {
		debug("Failed to write to remote");
		return LC_ERROR_WRITE;
	}

	uint8_t rsp[60];
	unsigned int len;
	uint8_t status;
	if ((err = Read(status, len, rsp))) {
		debug("failed to read from remote");
		return LC_ERROR_READ;
	}

	if (rsp[1] != TYPE_RESPONSE || rsp[2] != COMMAND_UPDATE_TIME) {
	    	return LC_ERROR;
	}

	return 0;
}
