slashTerminate( const string &src )
{
    string result = src;
    if( result[ result.length()-1 ] != '/' )
	result.append( "/" );
    return result;
}
