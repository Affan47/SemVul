assign( const char* str, size_type num )
    {
        std::string tmp;
        tmp.assign( str, num );
        return assign( tmp );
    }
