parse_value(lex_t *lex, json_error_t *error)
{
    json_t *json;

    switch(lex->token) {
        case TOKEN_STRING: {
            json = json_string_nocheck(lex->value.string);
            break;
        }

        case TOKEN_INTEGER: {
            json = json_integer(lex->value.integer);
            break;
        }

        case TOKEN_REAL: {
            json = json_real(lex->value.real);
            break;
        }

        case TOKEN_TRUE:
            json = json_true();
            break;

        case TOKEN_FALSE:
            json = json_false();
            break;

        case TOKEN_NULL:
            json = json_null();
            break;

        case '{':
            json = parse_object(lex, error);
            break;

        case '[':
            json = parse_array(lex, error);
            break;

        case TOKEN_INVALID:
            error_set(error, lex, "invalid token");
            return NULL;

        default:
            error_set(error, lex, "unexpected token");
            return NULL;
    }

    if(!json)
        return NULL;

    return json;
}
