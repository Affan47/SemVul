GetDBName(unsigned int number,
				 std::string &name) const
{
	DatabaseArrayType::const_iterator b = Databases.begin();
	for( ; b != Databases.end(); ++b )
		if( b->Number == number ) {
			name = b->Name;
			return true;
		}
	return false;
}
