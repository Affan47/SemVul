GetCommand(const std::string &name) const
{
	CommandArrayType::const_iterator b = Commands.begin();
	for( ; b != Commands.end(); b++ )
		if( b->Name == name )
			return b->Code;
	return 0;
}
