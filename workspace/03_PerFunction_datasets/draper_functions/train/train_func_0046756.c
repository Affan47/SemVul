reply_talk_msg()
{
	err_when( id != MSG_REPLY_TALK_MSG);


	int talkMsgRecno = *(int*)data_buf;

	if( !talk_res.is_talk_msg_deleted(talkMsgRecno) )
	{
#ifdef DEBUG_LONG_LOG
		long_log->printf("reply talk message %d, %d\n", talkMsgRecno, data_buf[sizeof(int)]);
#endif
		talk_res.reply_talk_msg( talkMsgRecno, data_buf[sizeof(int)], COMMAND_REMOTE);
	}


}
