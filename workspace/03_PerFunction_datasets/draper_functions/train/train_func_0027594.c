parse(const std::string& mediaType)
{
	_type.clear();
	_subType.clear();
	_parameters.clear();
	std::string::const_iterator it  = mediaType.begin();
	std::string::const_iterator end = mediaType.end();
	while (it != end && Poco::Ascii::isSpace(*it)) ++it;
	while (it != end && *it != '/') _type += *it++;
	if (it != end) ++it;
	while (it != end && *it != ';' && !Poco::Ascii::isSpace(*it)) _subType += *it++;
	while (it != end && *it != ';') ++it;
	MessageHeader::splitParameters(it, end, _parameters);
}
