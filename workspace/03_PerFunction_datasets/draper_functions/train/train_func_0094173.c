DP_CallBack(rlp_user_inds ind, unsigned char *buffer, int length)
{
	int i, temp;

	switch(ind) {
	case Data:
		if (CommandMode == false) write(PtyWRFD, buffer, length);
		break;
	case Conn_Ind:
		if (CommandMode == false) gn_atem_modem_result(MR_CARRIER);
		rlp_user_request_set(Conn_Req, true);
		break;
	case StatusChange:
		if (buffer[0] == 0) {
			connected = true;
			if (CommandMode == false) gn_atem_modem_result(MR_CONNECT);
		}
		break;
	case Disc_Ind:
		if (CommandMode == false) gn_atem_modem_result(MR_NOCARRIER);
		connected = false;

		data.call_notification = gn_atem_call_passup;
		gn_sm_functions(GN_OP_SetCallNotification, &data, sm);
		CommandMode = true;
		break;
	case Reset_Ind:
		rlp_user_request_set(Reset_Resp, true);
		break;
	case GetData:
		if (queue.n > 0) {
			temp = queue.n < sizeof(buffer) ? queue.n : sizeof(buffer);
			for (i = 0; i < temp; i++) {
				buffer[i] = queue.buf[queue.head++];
				queue.head %= sizeof(queue.buf);
				queue.n--;
			}


			if (buffer[0] == '+') {
				pluscount++;
				if (temp > 1) {
					if (buffer[1] == '+') pluscount++;
					else pluscount = 0;
					if (temp > 2) {
						if (buffer[2] == '+') pluscount++;
						else pluscount = 0;
						if (temp > 3) pluscount = 0;
					}
				}
			} else pluscount = 0;

			if (pluscount == 3) {
				CommandMode = true;

				data.call_notification = gn_atem_call_passup;
				gn_sm_functions(GN_OP_SetCallNotification, &data, sm);
				gn_atem_string_out("\r\n");
				gn_atem_modem_result(MR_OK);
				break;
			}

			return temp;
		}
		break;
	default:
		break;
	}
	return 0;
}
