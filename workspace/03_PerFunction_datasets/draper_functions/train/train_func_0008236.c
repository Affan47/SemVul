read(istream & is)
{
	string tmp;
	do {
		char c = is.peek();
		if (c == '[')
			break;
		getline(is, tmp);
		if (tmp == "" || tmp[0] == '#' || tmp[0] == ' ')
			continue;

		lastcommands.push_back(tmp);
	} while (is.good());
}
