HasNewIncomingConnection(void)
{
	unsigned i;
	SystemAddress newConnection;
	newConnection = tcpInterface->HasNewIncomingConnection();


	if (newConnection != UNASSIGNED_SYSTEM_ADDRESS)
	{
		unsigned char command[10];


		command[0]=255;

		command[1]=251;
		command[2]=1;
		tcpInterface->Send((const char*)command, 3, newConnection, false);


		TelnetClient *remoteClient=0;
		for (i=0; i < remoteClients.Size(); i++)
		{
			if (remoteClients[i]->systemAddress==newConnection)
			{
				remoteClient=remoteClients[i];
				remoteClient->cursorPosition=0;
			}
		}

		if (remoteClient==0)
		{
			remoteClient=new TelnetClient;
			remoteClient->lastSentTextInput[0]=0;
			remoteClient->cursorPosition=0;
			remoteClient->systemAddress=newConnection;
#ifdef _PRINTF_DEBUG
			memset(remoteClient->textInput, 0, REMOTE_MAX_TEXT_INPUT);
#endif
		}

		remoteClients.Insert(remoteClient, _FILE_AND_LINE_);
	}
	return newConnection;
}
