StringTokenizer( const std::string& str, const char delim )
{
    std::list< std::string > list_str;

    size_t i = 0, i2 = 0, lng = str.length();
    for(;;){

        while( i2 < lng && str[ i2++ ] != delim );
        int tmp = ( str[ i2-1 ] == delim || str[ i2 -1 ] == '\n' ) ? 1 : 0;
        if( i2 - i ) list_str.push_back( str.substr( i, i2 - i - tmp ) );
        if( i2 >= lng ) break;
        i = i2;
    }

    return list_str;
}
