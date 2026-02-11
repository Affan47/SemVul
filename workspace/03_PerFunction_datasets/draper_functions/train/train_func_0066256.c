parse_encoded_word (const std::string &line, std::string &charset,
							  std::string &encoding, std::string &text,
							  std::string::size_type &pos)
{
	std::string::size_type	i = pos, i1, i2;


	if ((i+1 >= line.size()) || (line[i] != '=') || (line[i+1] != '?'))
		return false;
	i += 2;


	if (!parse_encoded_word_search(line, pos, i))
		return false;
	i1 = i++;


	charset = ascii_strdown (line.substr (pos+2, i1-2-pos));


	if (!parse_encoded_word_search(line, pos, i))
		return false;
	i2 = i++;


	encoding = ascii_strdown (line.substr (i1+1, i2-1-i1));


	if (!parse_encoded_word_search(line, pos, i, true))
		return false;


	text = line.substr (i2+1, i-1-i2);
	pos = i+2;

	return true;
}
