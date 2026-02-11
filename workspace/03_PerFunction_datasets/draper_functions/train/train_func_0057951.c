balance_parentheses( const char * * s_, const char * * string, VAR_PARSE_GROUP * out)
{
    int depth = 1;
    const char * s = *s_;
    for ( ; ; )
    {
        if ( try_parse_variable( &s, string, out ) ) { }
        else if(s[0] == ':' || s[0] == '[')
        {
            parse_error( "unbalanced parentheses" );
            ++s;
        }
        else if(s[0] == '\0')
        {
            parse_error( "unbalanced parentheses" );
            break;
        }
        else if(s[0] == ')')
        {
            ++s;
            if(--depth == 0) break;
        }
        else if(s[0] == '(')
        {
            ++depth;
            ++s;
        }
        else
        {
            ++s;
        }
    }
    *s_ = s;
}
