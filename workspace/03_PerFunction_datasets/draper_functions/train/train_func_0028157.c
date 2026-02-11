GetChannelByUser(char *nickname)
{
	char szWhoisCmd[100];

	if(GettingUserChannel)
	{
		if(Getting_user_channel_error)
		{
			Getting_user_channel_error = 0;
			GettingUserChannel = 0;
			return (char *)-1;
		}
		if(*User_req_channel)
		{
			GettingUserChannel = 0;
			return User_req_channel;
		}
	}
	else
	{
		strncpy(Getting_user_channel_info_for, nickname, sizeof(Getting_user_channel_info_for)-1);
		User_req_channel[0] = '\0';
		snprintf(szWhoisCmd, SSIZE(szWhoisCmd), NOX("/WHOIS %s"), nickname);
		SendChatString(szWhoisCmd,1);
		GettingUserChannel = 1;
	}
	return NULL;
}
