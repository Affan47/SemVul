de_escape_path()
{
	string &p = peer->path;
	if (p.find("%") == string::npos)
		return 0;

	string tmp;
	tmp.resize(16);
	size_t pos = 0;
	unsigned char c = 0, c1, c2;
	tmp = "";
	while ((pos = p.find("%")) != string::npos) {

		if (pos > p.size() - 3)
			return -1;
		if (!isxdigit(p[pos + 1]) || !isxdigit(p[pos + 2]))
			return -1;
		c1 = toupper(p[pos + 1]);
		c2 = toupper(p[pos + 2]);
		if (c1 >= 'A' && c1 <= 'F')
			c = (10 + c1 - 'A')<<4;
		else
			c = (c1 - '0')<<4;
		if (c2 >= 'A' && c2 <= 'F')
			c += (10 + c2 - 'A');
		else
			c += (c2 - '0');
		tmp.push_back(c);
		p.replace(pos, 3, tmp, 0, 1);
		tmp = "";
	}
	return 0;
}
