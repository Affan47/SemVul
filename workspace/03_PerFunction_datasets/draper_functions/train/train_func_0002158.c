matchIdentifier()
{
    Lexer::Token tok = getNext();
    if (tok.type == Lexer::Ident)
        return tok.value;
    issueError("Expected identifier, got:" + tok.toString(lexer));
    return "";
}
