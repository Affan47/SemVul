lexer_advance(Lexer* lex)
{

    if (lexer_has_error(lex))
        return 0;

    while (_skip_ws(lex)) {
        switch (lex->curr[0]) {
        case '[':
            _store_token(lex, json_token_type_left_bracket, 1);
            return 1;
        case ']':
            _store_token(lex, json_token_type_right_bracket, 1);
            return 1;
        case '{':
            _store_token(lex, json_token_type_left_curly, 1);
            return 1;
        case '}':
            _store_token(lex, json_token_type_right_curly, 1);
            return 1;
        case ',':
            _store_token(lex, json_token_type_comma, 1);
            return 1;
        case ':':
            _store_token(lex, json_token_type_colon, 1);
            return 1;

        case '"': case '\'':
            return _parse_string(lex);

        case '+': case '-': case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7': case '8': case '9':
            return _parse_number(lex);

        case 't':
            if (_match_keyword(lex, "true")) {
                _store_token(lex, json_token_type_true, strlen("true"));
                return 1;
            }
            break;

        case 'f':
            if (_match_keyword(lex, "false")) {
                _store_token(lex, json_token_type_false, strlen("false"));
                return 1;
            }
            break;

        case 'n':
            if (_match_keyword(lex, "null")) {
                _store_token(lex, json_token_type_null, strlen("null"));
                return 1;
            }
            break;

        case '/':
            if (_skip_comment(lex)) {
                if (lexer_has_error(lex))
                    return 0;
                continue;
            }
        }

        if (_match_identifier(lex)) {
            return _parse_identifier(lex);
        }

        lex->error = lexer_error_unexpected_input;
        return 0;
    }

    lex->error = lexer_error_input_exhausted;
    return 0;
}
