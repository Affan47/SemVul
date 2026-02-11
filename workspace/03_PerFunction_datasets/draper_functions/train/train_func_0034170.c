G_Oros3OpenComm(const INT16 port_no, WORD32 BaudRate)
{


	TGTSER_PORT comm;
	BYTE r_buff[HOR3GLL_OS_STRING_SIZE];
	WORD16 r_len;
	WORD32 end_time;
	INT16 portcom, response;

	comm.Port = port_no;


	comm.BaudRate = BaudRate;


	comm.Mode = HGTSER_WORD_8 + HGTSER_NO_PARITY + HGTSER_STOP_BIT_1;
	comm.TimeOut = HOR3COMM_CHAR_TIMEOUT;
	comm.TxSize = HGTGBP_MAX_BUFFER_SIZE;
	comm.RxSize = HGTGBP_MAX_BUFFER_SIZE;

	response = portcom = G_SerPortOpen(&comm);

	DEBUG_MSG("G_SerPortOpenCalled");

	if (response < G_OK)
	{
		return (response);
	}

	DEBUG_MSG("G_SerPortOpenCalled-checked resp");


	G_GBPOpen(2, 4, portcom);

	DEBUG_MSG("Come after G_GBPOpen");

	do
	{
		wait_ms (HOR3COMM_CHAR_TIME);

		r_len = HOR3GLL_IFD_LEN_VERSION + 1;

		response = G_Oros3Exchange (HOR3GLL_LOW_TIME,
			5, (BYTE G_FAR *) ("\x22\x05\x3F\xE0\x0D"), &r_len, r_buff);
		DEBUG_MSG("In Oros3OpenComm: resp=%d", response);

		if (response < G_OK)
		{


			if (comm.BaudRate == 9600L)
			{
				comm.BaudRate = 38400L;
			}

			else
			{
				G_GBPClose();

				G_SerPortClose(portcom);

				return (GE_IFD_MUTE);
			}
			response = G_SerPortSetState(&comm);

			if (response < G_OK)
			{
				G_GBPClose();

				G_SerPortClose(portcom);

				return (response);
			}
		} else
		{
			break;
		}
	}
	while (r_len != (HOR3GLL_IFD_LEN_VERSION + 1));

	return (G_OK);
}
