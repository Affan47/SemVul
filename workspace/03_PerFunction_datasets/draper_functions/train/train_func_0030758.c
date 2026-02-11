shut_packet_recv(int upsfd, u_char *Buf, int datalen)
{
	u_char   Start[2];
	u_char   Frame[8];
	u_char   Chk[1];
	u_short  Size=8;
	u_short  Pos=0;
	u_char   Retry=0;
	int recv;


	upsdebugx (4, "entering shut_packet_recv (%i)", datalen);

	while(datalen>0 && Retry<3)
	{

		if(ser_get_char(upsfd, &Start[0], SHUT_TIMEOUT/1000, 0) > 0)
		{

			if(Start[0]==SHUT_SYNC)
			{
				upsdebugx (4, "received SYNC token");
				memcpy(Buf, Start, 1);
				return 1;
			}
			else if(Start[0]==SHUT_SYNC_OFF)
			{
				upsdebugx (4, "received SYNC_OFF token");
				memcpy(Buf, Start, 1);
				return 1;
			}
			else
			{

				if( (ser_get_char(upsfd, &Start[1], SHUT_TIMEOUT/1000, 0) > 0) &&
							((Start[1]>>4)==(Start[1]&0x0F)))
				{
					upsdebug_hex(4, "Receive", Start, 2);
					Size=Start[1]&0x0F;
					if( Size > 8 ) {
						upsdebugx (4, "shut_packet_recv: invalid frame size = %d", Size);
						ser_send_char(upsfd, SHUT_NOK);
						Retry++;
						break;
					}

					for(recv=0;recv<Size;recv++)
					{

						if(ser_get_char(upsfd, &Frame[recv], SHUT_TIMEOUT/1000, 0) < 1)
							break;
					}
					upsdebug_hex(4, "Receive", Frame, Size);


					ser_get_char(upsfd, &Chk[0], SHUT_TIMEOUT/1000, 0);
					if(Chk[0]==shut_checksum(Frame, Size))
					{
						upsdebugx (4, "shut_checksum: %02x => OK", Chk[0]);
						memcpy(Buf, Frame, Size);
						datalen-=Size;
						Buf+=Size;
						Pos+=Size;
						Retry=0;

						ser_send_char(upsfd, SHUT_OK);


						if((Start[0] & 0xf0) == SHUT_PKT_LAST)
						{

							if ((Start[0] & 0x0f) == SHUT_TYPE_NOTIFY)
							{

								upsdebugx (4, "=> notification");
								datalen+=Pos;
								Pos=0;
							}
							else
								return Pos;
						}
						else
							upsdebugx (4, "need more data (%i)!", datalen);
					}
					else
					{
						upsdebugx (4, "shut_checksum: %02x => NOK", Chk[0]);
						ser_send_char(upsfd, SHUT_NOK);

						Retry++;
					}
				}
				else
					return 0;
			}
		}
		else
			Retry++;
	}

	return 0;
}
