parse(const std::string& line, Poco::Message& message)
{

	std::size_t pos = 0;
	RemoteSyslogChannel::Severity severity;
	RemoteSyslogChannel::Facility fac;
	parsePrio(line, pos, severity, fac);


	if (Poco::Ascii::isDigit(line[pos]))
	{
		parseNew(line, severity, fac, pos, message);
	}
	else
	{
		parseBSD(line, severity, fac, pos, message);
	}
	poco_assert (pos == line.size());
}
