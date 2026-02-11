UT_XML_cloneNoAmpersands( const std::string& src )
{
    gchar* rszDest = 0;

    bool rc = UT_XML_cloneNoAmpersands( rszDest, src.c_str() );
    if( !rc )
        return src;

    std::string ret = rszDest;
    FREEP(rszDest);
    return ret;
}
