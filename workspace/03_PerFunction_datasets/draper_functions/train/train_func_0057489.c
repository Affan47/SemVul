cut_str( const std::string& str, const std::string& str1, const std::string& str2 )
{
    size_t i = str.find( str1 );
    if( i == std::string::npos ) return std::string();
    i += str1.length();
    size_t i2 = str.find( str2, i );
    if( i2 == std::string::npos ) return std::string();

    return str.substr( i, i2 - i );
}
