dump(const std::string& msg, const void* buffer, std::size_t length, Message::Priority prio)
{
	if (_level >= prio && _pChannel)
	{
		std::string text(msg);
		formatDump(text, buffer, length);
		_pChannel->log(Message(_name, text, prio));
	}
}
