parseOperation()
{

    match(Lexer::Operation);

    const Flag opFlags[] = {
        {"endsBB", Op_EndsBB},
        {"hint",   Op_Hint},
        {0, 0}
    };

    std::string name = matchIdentifier();
    unsigned flags   = matchFlags(opFlags);

    handleOperation(name, flags);

    match(Lexer::LBrace);
    Lexer::Token tok = peekNext();
    while (tok.type == Lexer::Tile || tok.type == Lexer::Impl) {
        if (tok.type == Lexer::Tile)
            parseTile();
        else
            parseImpl();
        tok = peekNext();
    }
    match(Lexer::RBrace);
}
