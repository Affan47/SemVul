chat_msg(int fromNationRecno, char* chatStr)
{


	int useChatId=0;
	int minDate=info.game_date+1;

	for( int i=0; i<MAX_REMOTE_CHAT_STR ; i++ )
	{
		if( info.remote_chat_array[i].received_date < minDate )
		{
			minDate	 = info.remote_chat_array[i].received_date;
			useChatId = i+1;
		}
	}

	if( useChatId )
	{
		ChatInfo* chatInfo = info.remote_chat_array+useChatId-1;

		chatInfo->received_date = info.game_date;
		chatInfo->from_nation_recno = fromNationRecno;

		strncpy( chatInfo->chat_str, chatStr, CHAT_STR_LEN );
		chatInfo->chat_str[CHAT_STR_LEN] = '\0';
	}


	News* newsPtr = add_news( NEWS_CHAT_MSG, NEWS_NORMAL, fromNationRecno);

	if( !newsPtr )
		return;

	newsPtr->short_para1 = useChatId;
}
