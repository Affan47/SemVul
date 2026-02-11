log(const string msg, const message_type type, int iline)
{
	message new_msg;
	new_msg.m = msg;
	new_msg.t = type;
	if(iline == 0)
	{
		iline = line;
	}
	if(logs.count(line) > 0)
	{
		for(int i = 0; i < logs[line].size(); ++i)
		{
			if(logs[line][i].m == new_msg.m && logs[line][i].t == new_msg.t)
			{
				return;
			}
		}
	}
	logs[line].push_back(new_msg);
}
