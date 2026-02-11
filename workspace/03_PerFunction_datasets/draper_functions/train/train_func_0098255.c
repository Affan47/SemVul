GetFullName() const
{
	std::string Full = FirstName;
	if( Full.size() && LastName.size() )
		Full += " ";
	Full += LastName;
	return Full;
}
