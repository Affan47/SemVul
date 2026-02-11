_skip_ws(Lexer* lex)
{
    char c;
    while (isspace(c = lex->curr[0])) {
        if (!_skip_newline(lex)) {
            lex->curr++;
        }
    }
    return lex->curr < lex->end;
}
