IncomingRLPFrame(int messagetype, unsigned char *message, int length, gn_data *data, struct gn_statemachine *state)
{
	gn_rlp_f96_frame frame;


	if (!DRVINSTANCE(state)->rlp_rx_callback) return GN_ERR_NONE;


	if (message[0] == 0xd9 && message[1] == 0x01) {
		DRVINSTANCE(state)->rlp_rx_callback(NULL);
		return GN_ERR_NONE;
	}


	frame.Header[0] = message[2];
	frame.Header[1] = message[3];


	memcpy(frame.Data, message + 4, 25);


	frame.FCS[0] = message[29];
	frame.FCS[1] = message[30];
	frame.FCS[2] = message[31];


	DRVINSTANCE(state)->rlp_rx_callback(&frame);

	return GN_ERR_NONE;
}
