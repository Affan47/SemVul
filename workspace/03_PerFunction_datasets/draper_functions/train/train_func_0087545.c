newPrefix()
{
	std::ostringstream str;
	str << "ns" << ++_prefix;
	return toXMLString(str.str());
}
