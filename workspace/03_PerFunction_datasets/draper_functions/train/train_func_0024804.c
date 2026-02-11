G_Oros3ReadResp
	(const WORD32 Timeout, WORD16 G_FAR * RspLen, WORD8 G_FAR Rsp[])
{


	INT16 response, portcom;
#if (defined WIN32) || (defined G_OS2) || (defined G_UNIX)
	WORD16 r_len;
	BYTE r_buff[HGTGBP_MAX_BUFFER_SIZE];
#endif


	portcom = G_GBPChannelToPortComm();


	r_len = 3;
	response = G_SerPortRead(portcom, &r_len, r_buff);
	if (response < G_OK)
	{
		*RspLen = 0;
		return (response);
	}


	r_len = (WORD16) (r_buff[2] + 1);


	response = G_SerPortRead(portcom, &r_len, r_buff + 3);

	if (response < G_OK)
	{
		*RspLen = 0;
		return (response);
	}


	r_len += 3;

	DEBUG_XXD("BGP Resp: ", r_buff, r_len);


	response = G_GBPDecodeMessage(r_len, r_buff, RspLen, Rsp);

	return response;
}
