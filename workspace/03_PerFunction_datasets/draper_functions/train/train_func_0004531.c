_parse_string(Lexer* lex)
{


    if (lex->curr[0] != '"' && lex->curr[0] != '\'') {
        JSON_PANIC(("Current token must begin with \" or '."));
    }

    Str* answer = str_create(16);
    const char* p = lex->curr + 1;
    const char terminator = lex->curr[0];

    for (; p < lex->end; p++) {
        if (*p == terminator) {
            lex->token.type = json_token_type_string;
            lex->token.value.string = _copy_str_into_lexer(lex, answer);
            str_destroy(answer);
            lex->curr = p + 1;
            return 1;
        } else if (*p == '\\') {
            if (p[1] == terminator) {
                str_append_char(&answer, *++p);
                continue;
            }
            switch (p[1]) {
            case '\\': case '/':
                str_append_char(&answer, p[1]);
                break;
            case 'b':
                str_append_char(&answer, '\b');
                break;
            case 'f':
                str_append_char(&answer, '\f');
                break;
            case 'n':
                str_append_char(&answer, '\n');
                break;
            case 'r':
                str_append_char(&answer, '\r');
                break;
            case 't':
                str_append_char(&answer, '\t');
                break;
            case 'u':
                JSON_PANIC(("unicode not supported yet"));
                break;
            default:

                lex->error = lexer_error_illegal_escape_sequence;
                return 0;
            }
            p++;
        } else if (*p == '\n' || *p == '\r') {
            if (*p == '\r' && *(p+1) == '\n') {
                str_append_char(&answer, *p++);
            }
            str_append_char(&answer, *p);
            _next_line(lex);
        } else {
            str_append_char(&answer, *p);
        }
    }


    lex->error = lexer_error_runaway_string;
    str_destroy(answer);
    return 0;
}
