TCPSendAndCheck(uint8_t cmd, uint32_t len, uint8_t *data)
{
	int err = 0;
	uint8_t status;
	unsigned int rlen;
	uint8_t rsp[60];

	if ((err = Write(TYPE_REQUEST, cmd, len, data))) {
		debug("Failed to send request %02X", cmd);
		return LC_ERROR_WRITE;
	}

	if ((err = Read(status, rlen, rsp))) {
		debug("Failed to read from remote");
		return LC_ERROR_READ;
	}

	if (rsp[2] != TYPE_RESPONSE) {
		debug("Packet didn't have response bit!");
		return LC_ERROR;
	}

	if (rsp[1] != cmd) {
		debug("The cmd bit didn't match our request packet");
		return LC_ERROR;
	}

	return 0;
}
