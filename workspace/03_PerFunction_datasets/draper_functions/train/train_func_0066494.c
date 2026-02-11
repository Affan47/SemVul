ChannelPutModifiable2(const std::string &channel, byte *begin, size_t length, int messageEnd, bool blocking)
{
	if (channel.empty())
		return PutModifiable2(begin, length, messageEnd, blocking);
	else
		return ChannelPut2(channel, begin, length, messageEnd, blocking);
}
