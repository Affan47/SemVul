decode_quotedprintable (const std::string &todec)
{
	std::string::size_type pos = 0, len = todec.length();
	std::string result;
	gint decoded;

	while (pos < len)
	{
		switch (gchar c = todec.at(pos++))
		{
			case '=':
				pos += 2;
				if (pos > len)
					return result;
				if ((decoded  = g_ascii_xdigit_value(todec.at(pos-1))) < 0)
					return std::string("");
				if ((decoded += 16*g_ascii_xdigit_value(todec.at(pos-2))) < 0)
					return std::string("");
				result += decoded;
				break;
			default:
				result += c;
				break;
		}
	}
	return result;
}
