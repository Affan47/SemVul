CopyRangeTo2(BufferedTransformation &target, lword &begin, lword end, const std::string &channel, bool blocking) const
{
	static const byte nullBytes[128] = {0};
	while (begin < end)
	{
		size_t len = (size_t)STDMIN(end-begin, lword(128));
		size_t blockedBytes = target.ChannelPut2(channel, nullBytes, len, 0, blocking);
		if (blockedBytes)
			return blockedBytes;
		begin += len;
	}
	return 0;
}
