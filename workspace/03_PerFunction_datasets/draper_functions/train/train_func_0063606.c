adsi_get_cpeid(struct ast_channel *chan, unsigned char *cpeid, int voice)
{
	unsigned char buf[256] = "";
	int bytes = 0, res;

	bytes += adsi_data_mode(buf);
	adsi_transmit_message_full(chan, buf, bytes, ADSI_MSG_DISPLAY, 0);

	bytes = 0;
	bytes += adsi_query_cpeid(buf);
	adsi_transmit_message_full(chan, buf, bytes, ADSI_MSG_DISPLAY, 0);


	res = adsi_read_encoded_dtmf(chan, cpeid, 4);
	if (res != 4) {
		ast_log(LOG_WARNING, "Got %d bytes back of encoded DTMF, expecting 4\n", res);
		res = 0;
	} else {
		res = 1;
	}

	if (voice) {
		bytes = 0;
		bytes += adsi_voice_mode(buf, 0);
		adsi_transmit_message_full(chan, buf, bytes, ADSI_MSG_DISPLAY, 0);

		ast_waitfordigit(chan, 1000);
	}
	return res;
}
