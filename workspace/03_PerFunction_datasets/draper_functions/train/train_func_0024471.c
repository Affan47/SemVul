getJtagResponse(int responseSize)
{
    uchar *response;
    int numCharsRead;


    response = new uchar[responseSize + 1];
    response[responseSize] = '\0';

    numCharsRead = timeout_read(response, responseSize,
                                JTAG_RESPONSE_TIMEOUT);
    jtagCheck(numCharsRead);

    debugOut("response: ");
    for (int i = 0; i < numCharsRead; i++)
    {
	debugOut("%.2X ", response[i]);
    }
    debugOut("\n");

    if (numCharsRead < responseSize)
    {
	debugOut("Timed Out (partial response)\n");
	delete [] response;
	return NULL;
    }

    return response;
}
