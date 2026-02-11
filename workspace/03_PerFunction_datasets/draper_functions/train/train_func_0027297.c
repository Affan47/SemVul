getFullName() const
{
	size_t csize = ckdb::keyGetFullNameSize (getKey());
	std::string str;
	char * field = new char [csize];

	ckdb::keyGetFullName (getKey(), field, csize);
	str = field;
	delete [] field;
	return str;
}
