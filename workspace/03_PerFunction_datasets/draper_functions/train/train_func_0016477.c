MimeToBabelType (char const *mime_type)
{
	std::map <std::string, std::string>::iterator it = m_BabelTypes.find (mime_type);
	return (it == m_BabelTypes.end ())? mime_type: (*it).second.c_str ();
}
