load(std::istream& istr)
{
	clear();
	while (!istr.eof())
	{
		parseLine(istr);
	}
}
