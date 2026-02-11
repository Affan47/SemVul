Send(  SystemAddress systemAddress, const char *data,... )
{
	if (tcpInterface==0) return;

	if (data==0 || data[0]==0)
		return;

	char text[REMOTE_MAX_TEXT_INPUT];
	size_t prefixLength;
	if (sendPrefix)
	{
		strcpy(text, sendPrefix);
		prefixLength = strlen(sendPrefix);
	}
	else
	{
		text[0]=0;
		prefixLength=0;
	}
	va_list ap;
	va_start(ap, data);
	_vsnprintf(text+prefixLength, REMOTE_MAX_TEXT_INPUT-prefixLength, data, ap);
	va_end(ap);
	text[REMOTE_MAX_TEXT_INPUT-1]=0;

	if (sendSuffix)
	{
		size_t length = strlen(text);
		size_t availableChars = REMOTE_MAX_TEXT_INPUT-length-1;
		strncat(text, sendSuffix, availableChars);
	}

	tcpInterface->Send(text, (unsigned int) strlen(text), systemAddress, false);
}
