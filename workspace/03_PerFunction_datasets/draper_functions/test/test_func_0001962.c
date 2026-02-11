adsi_load_session(struct ast_channel *chan, unsigned char *app, int ver, int data)
{
	unsigned char dsp[256] = "";
	int bytes = 0, res;
	char resp[2];


	bytes += adsi_connect_session(dsp + bytes, app, ver);

	if (data) {
		bytes += adsi_data_mode(dsp + bytes);
	}


	if (adsi_transmit_message_full(chan, dsp, bytes, ADSI_MSG_DISPLAY, 0)) {
		return -1;
	}
	if (app) {
		if ((res = ast_readstring(chan, resp, 1, 1200, 1200, "")) < 0) {
			return -1;
		}
		if (res) {
			ast_debug(1, "No response from CPE about version.  Assuming not there.\n");
			return 0;
		}
		if (!strcmp(resp, "B")) {
			ast_debug(1, "CPE has script '%s' version %d already loaded\n", app, ver);
			return 1;
		} else if (!strcmp(resp, "A")) {
			ast_debug(1, "CPE hasn't script '%s' version %d already loaded\n", app, ver);
		} else {
			ast_log(LOG_WARNING, "Unexpected CPE response to script query: %s\n", resp);
		}
	} else
		return 1;
	return 0;

}
