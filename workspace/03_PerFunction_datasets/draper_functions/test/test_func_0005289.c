resolveService(const std::string& service)
{
	unsigned port;
	if (NumberParser::tryParseUnsigned(service, port) && port <= 0xFFFF)
	{
		return (UInt16) port;
	}
	else
	{
#if defined(POCO_VXWORKS)
		throw ServiceNotFoundException(service);
#else
		struct servent* se = getservbyname(service.c_str(), NULL);
		if (se)
			return ntohs(se->s_port);
		else
			throw ServiceNotFoundException(service);
#endif
	}
}
