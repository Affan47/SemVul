GetAppNames() const
{
	std::string names;

	const_iterator b = begin(), e = end();
	for( ; b != e; ++b ) {
		std::string name = (*b)->GetAppName();
		if( name != Config::Barry::AppName() ) {
			if( names.size() )
				names += ", ";
			names += name;
		}
	}

	return names;
}
