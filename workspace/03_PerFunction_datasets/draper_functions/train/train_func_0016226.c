st_ReadEscapeSequence( char & c, std::istream & s )
{
    char c2 = '\0';
    bool ret = st_ReadEscapeSequence( c, c2, s );
    if ( c2 && s.good() )
    {
        s.putback( c2 );
    }
    return ret;
}
