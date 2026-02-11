operator>>(std::istream& in, Integer &a)
{
	char c;
	unsigned int length = 0;
	SecBlock<char> str(length + 16);

	std::ws(in);

	do
	{
		in.read(&c, 1);
		str[length++] = c;
		if (length >= str.size())
			str.Grow(length + 16);
	}
	while (in && (c=='-' || c=='x' || (c>='0' && c<='9') || (c>='a' && c<='f') || (c>='A' && c<='F') || c=='h' || c=='H' || c=='o' || c=='O' || c==',' || c=='.'));

	if (in.gcount())
		in.putback(c);
	str[length-1] = '\0';
	a = Integer(str);

	return in;
}
