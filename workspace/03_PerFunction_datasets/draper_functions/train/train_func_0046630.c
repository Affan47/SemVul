read( std::stringstream &f )
{


	std::string tmpStr;

	f >> tmpStr;

	_value = tmpStr;

	setInitState( true );

	return true;

}
