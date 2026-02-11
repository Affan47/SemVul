save_messages(char *String, int channel, int stat)
{
	int RetCode;


	if (stat == STATE_HANGUP)
	{
		if ((RetCode = del_Cur_Info(channel)) < 0)
		{
			print_msg(PRT_DEBUG_CS,"Invalid Channel No. %d\n",channel);
		}

		if ((RetCode = append_Old_Info(String)) < 0)
			return RetCode;
	}
	else
	{
		if ((RetCode = add_Cur_Info(channel,String)) < 0)
			return RetCode;
	}

	return 0;
}
