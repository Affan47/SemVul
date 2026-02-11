parse_long_option( const char * const opt, const char * const arg,
                               const Option options[], int & argind ) throw()
{
    unsigned int len;
    int index = -1;
    bool exact = false, ambig = false;

    for( len = 0; opt[len+2] && opt[len+2] != '='; ++len ) ;


    for( int i = 0; options[i].code != 0; ++i )
        if( options[i].name && !std::strncmp( options[i].name, &opt[2], len ) )
            {
                if( std::strlen( options[i].name ) == len )
                    { index = i; exact = true; break; }
                else if( index < 0 ) index = i;
                else if( options[index].code != options[i].code ||
                         options[index].has_arg != options[i].has_arg )
                    ambig = true;
            }

    if( ambig && !exact ) {
        _error = "option `"; _error += opt; _error += "' is ambiguous";
        return false;
    }

    if( index < 0 ) {
        _error = "unrecognized option `"; _error += opt; _error += '\'';
        return false;
    }

    ++argind;
    data.push_back( Record( options[index].code ) );

    if(opt[len+2])	{
        if( options[index].has_arg == no ) {
            _error = "option `--"; _error += options[index].name;
            _error += "' doesn't allow an argument";
            return false;
        }
        if( options[index].has_arg == yes && !opt[len+3] ) {
            _error = "option `--"; _error += options[index].name;
            _error += "' requires an argument";
            return false;
        }
        data.back().argument = &opt[len+3];
        return true;
    }

    if( options[index].has_arg == yes ) {
        if( !arg ) {
            _error = "option `--"; _error += options[index].name;
            _error += "' requires an argument";
            return false;
        }
        ++argind; data.back().argument = arg;
        return true;
    }

    return true;
}
