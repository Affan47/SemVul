shut_packet_send (hid_data_t *hdata, int datalen, u_char token)
{
	shut_packet_t SHUTRequest;
	shut_data_t   sdata;
	short Retry=1;
	short Size;
	int i;

	upsdebugx (3, "entering shut_packet_send (%i)", datalen);

	while(datalen>0 && Retry>0)
	{
		Size=(datalen>=8) ? 8 : datalen;


		if (Retry == 1) {


			SHUTRequest.bType = SHUT_TYPE_REQUEST + token;
			SHUTRequest.bLength = (Size<<4) + Size;
			SHUTRequest.data = *hdata;


			sdata.shut_pkt = SHUTRequest;
			sdata.raw_pkt[(Size+3) - 1] = shut_checksum(sdata.shut_pkt.data.raw_pkt, Size);

			upsdebugx (4, "shut_checksum = %2x", sdata.raw_pkt[(Size+3)-1]);

			serial_send (sdata.raw_pkt, Size+3);
		}
		i = shut_wait_ack ();
		if (i == 0) {
			datalen-=Size;
			Retry=5;

			upsdebugx (4, "received ACK");
			break;
		} else if ((i == -1) || (i == -3)) {


			if (Retry >= MAX_TRY) {
				upsdebugx(2, "Max tries reached while waiting for ACK, still getting errors");
 				return i;
			} else {
				upsdebugx(4, "Retry = %i", Retry);

				shut_token_send(SHUT_NOK);
				Retry++;
			}
		}
	}
	return (datalen==0);
}
