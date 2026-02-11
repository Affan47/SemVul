getChannel(const QHostAddress &addr, int port)
	{
		for(int n = 0; n < channels.count(); ++n)
		{
			if(channels[n]->active && channels[n]->addr == addr && channels[n]->port == port)
				return channels[n]->channelId;
		}

		return -1;
	}
