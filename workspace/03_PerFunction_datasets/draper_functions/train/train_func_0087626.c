istitle( const std::string & str )
    {
        std::string::size_type len = str.size(), i;

        if ( len == 0 ) return false;
        if ( len == 1 ) return ::isupper( str[0] );

        bool cased = false, previous_is_cased = false;

        for ( i = 0; i < len; ++i )
        {
            if ( ::isupper( str[i] ) )
            {
                if ( previous_is_cased )
                {
                    return false;
                }

                previous_is_cased = true;
                cased = true;
            }
            else if ( ::islower( str[i] ) )
            {
                if (!previous_is_cased)
                {
                    return false;
                }

                previous_is_cased = true;
                cased = true;

            }
            else
            {
                previous_is_cased = false;
            }
        }

        return cased;
    }
