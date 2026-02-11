key_name_state( struct parser *parser, const WCHAR *pos )
{
    const WCHAR *p, *token_end = parser->start;

    for (p = pos; !is_eol( parser, p ); p++)
    {
        if (*p == ',') break;
        switch(*p)
        {

         case '=':
            push_token( parser, token_end );
            if (!add_field_from_token( parser, 1 )) return NULL;
            parser->start = p + 1;
            push_state( parser, VALUE_NAME );
            set_state( parser, LEADING_SPACES );
            return p + 1;
        case ';':
            push_token( parser, token_end );
            if (!add_field_from_token( parser, 0 )) return NULL;
            push_state( parser, LINE_START );
            set_state( parser, COMMENT );
            return p + 1;
        case '"':
            push_token( parser, token_end );
            parser->start = p + 1;
            push_state( parser, KEY_NAME );
            set_state( parser, QUOTES );
            return p + 1;
        case '\\':
            push_token( parser, token_end );
            parser->start = p;
            push_state( parser, KEY_NAME );
            set_state( parser, EOL_BACKSLASH );
            return p;
        default:
            if (!isspaceW(*p)) token_end = p + 1;
            else
            {
                push_token( parser, p );
                push_state( parser, KEY_NAME );
                set_state( parser, TRAILING_SPACES );
                return p;
            }
            break;
        }
    }
    push_token( parser, token_end );
    set_state( parser, VALUE_NAME );
    return p;
}
