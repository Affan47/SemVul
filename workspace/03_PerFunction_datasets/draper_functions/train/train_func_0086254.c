getOption(int level, int option, IPAddress& value)
{
	char buffer[IPAddress::MAX_ADDRESS_LENGTH];
	poco_socklen_t len = sizeof(buffer);
	getRawOption(level, option, buffer, len);
	value = IPAddress(buffer, len);
}
