peekNext()
{
    if (!tokenLoaded) {
        nextToken   = lexer->nextToken();
        tokenLoaded = true;
    }

    return nextToken;
}
