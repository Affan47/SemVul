RTSP_ParseResponseHeader(GF_RTSPSession *sess, GF_RTSPResponse *rsp, u32 BodyStart)
{
	char LineBuffer[1024];
	char ValBuf[400];
	char *buffer;
	s32 Pos, ret;
	u32 Size;

	Size = sess->CurrentSize - sess->CurrentPos;
	buffer = sess->TCPBuffer + sess->CurrentPos;


	ret = gf_token_get_line(buffer, 0, Size, LineBuffer, 1024);
	if (ret < 0) return GF_REMOTE_SERVICE_ERROR;

	Pos = gf_token_get(LineBuffer, 0, " \t\r\n", ValBuf, 400);
	if (Pos <= 0) return GF_REMOTE_SERVICE_ERROR;
	if (strcmp(ValBuf, GF_RTSP_VERSION)) return GF_SERVICE_ERROR;

	Pos = gf_token_get(LineBuffer, Pos, " \t\r\n", ValBuf, 400);
	if (Pos <= 0) return GF_REMOTE_SERVICE_ERROR;
	rsp->ResponseCode = atoi(ValBuf);

	Pos = gf_token_get(LineBuffer, Pos, "\t\r\n", ValBuf, 400);
	if (Pos > 0) rsp->ResponseInfo = gf_strdup(ValBuf);

	return gf_rtsp_parse_header(buffer + ret, Size - ret, BodyStart, NULL, rsp);
}
