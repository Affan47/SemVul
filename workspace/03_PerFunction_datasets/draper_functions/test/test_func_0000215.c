match(Lexer::TokenType t)
{
    Lexer::Token tok = getNext();
    if (tok.type != t)
        issueError("Expected " + Lexer::Token(t).toString(lexer) + " got:" + tok.toString(lexer));
}
