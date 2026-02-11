toString() const
{
	std::string s;
	for (const_iterator it=begin();it!=end();++it)
	{
		if (it!=begin()) s+=", ";
		s+=std::string( (*it)->className );
	}
	return s;
}
