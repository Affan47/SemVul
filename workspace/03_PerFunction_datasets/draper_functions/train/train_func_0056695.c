read( std::stringstream &f )
{


	std::string tmpStr;
	f >> tmpStr;

	int tmpVal = atoi( tmpStr.c_str() );
	double tmpVal2 =  atof( tmpStr.c_str() );

	if (( tmpStr != "0" ) && ( tmpVal == 0 ) )
	{
		std::cerr << "Error (IntegerElement): Entry " << getOffset() + 1 << " in \"<"
		<< getParentName() << "></" << getParentName() << ">\" - Section is not a valid integer number!\n";
		return false;
	}

	if (( double )tmpVal != tmpVal2 )
	{
		std::cerr << "Error (IntegerElement): Entry " << getOffset() + 1 << " in \"<"
		<< getParentName() << "></" << getParentName() << ">\" - Section is a floating point number!\n";
		return false;
	}
	_value = tmpVal;

	setInitState( true );

	return true;

}
