IPAddressMatch(const char *IP)
{
	unsigned characterIndex;

	if ( IP == 0 || IP[ 0 ] == 0 || strlen( IP ) > 15 )
		return false;

	characterIndex = 0;

#ifdef _MSC_VER
#pragma warning( disable : 4127 )
#endif
	while ( true )
	{
		if (sharedString->c_str[ characterIndex ] == IP[ characterIndex ] )
		{

			if ( IP[ characterIndex ] == 0 )
			{


				return true;
			}

			characterIndex++;
		}

		else
		{
			if ( sharedString->c_str[ characterIndex ] == 0 || IP[ characterIndex ] == 0 )
			{

				break;
			}


			if ( sharedString->c_str[ characterIndex ] == '*' )
			{

				return true;
			}


			break;
		}
	}


	return false;
}
