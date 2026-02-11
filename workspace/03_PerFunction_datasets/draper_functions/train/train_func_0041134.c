removeChannel(Channel* pChannel)
{
	FastMutex::ScopedLock lock(_mutex);

	for (ChannelVec::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (*it == pChannel)
		{
			pChannel->release();
			_channels.erase(it);
			break;
		}
	}
}
