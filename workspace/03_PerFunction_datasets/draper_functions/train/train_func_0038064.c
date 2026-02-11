LogConnectionAttempts(RakNet::RakString &rs)
{
	rs.Clear();
	unsigned int index;
	char guidStr[128], ipStr[128];
	guid.ToString(guidStr);
	systemAddress.ToString(true,ipStr);
	rs=RakNet::RakString("User systemAddress=%s guid=%s\n", ipStr, guidStr);
	rs+=RakNet::RakString("%i attempts in list:\n", connectionAttempts.Size());
	for (index=0; index < connectionAttempts.Size(); index++)
	{
		rs+=RakNet::RakString("%i. SessionID=%i ", index+1, connectionAttempts[index]->sessionId);
		if (connectionAttempts[index]->sender==this)
			rs+="(We are sender) ";
		else
			rs+="(We are recipient) ";
		if (isReady)
			rs+="(READY TO START) ";
		else
			rs+="(NOT READY TO START) ";
		if (connectionAttempts[index]->attemptPhase==NatPunchthroughServer::ConnectionAttempt::NAT_ATTEMPT_PHASE_NOT_STARTED)
			rs+="(NOT_STARTED). ";
		else
			rs+="(GETTING_RECENT_PORTS). ";
		if (connectionAttempts[index]->sender==this)
		{
			connectionAttempts[index]->recipient->guid.ToString(guidStr);
			connectionAttempts[index]->recipient->systemAddress.ToString(true,ipStr);
		}
		else
		{
			connectionAttempts[index]->sender->guid.ToString(guidStr);
			connectionAttempts[index]->sender->systemAddress.ToString(true,ipStr);
		}

		rs+=RakNet::RakString("Target systemAddress=%s, guid=%s.\n", ipStr, guidStr);
	}
}
