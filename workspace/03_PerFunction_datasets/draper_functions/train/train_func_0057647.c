packetHeaderOverhead(const QHostAddress &addr, int port) const
{
	int channelId = d->getChannel(addr, port);

	if(channelId != -1)
	{

		if(d->pool->mode() == StunTransaction::Udp)
			return 4;
		else
			return 4 + 3;
	}
	else
	{

		if(d->dfState == StunAllocate::Private::DF_Supported)
		{

			return 40 + 3;
		}
		else
		{

			return 36 + 3;
		}
	}

	return -1;
}
