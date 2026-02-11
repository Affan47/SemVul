parseVersionCondition()
{
    Condition *c;
    unsigned level = 1;
    Identifier *id = NULL;

    if (token.value == TOKlparen)
    {
        nextToken();
        if (token.value == TOKidentifier)
            id = token.ident;
        else if (token.value == TOKint32v || token.value == TOKint64v)
            level = (unsigned)token.uns64value;
#if DMDV2


        else if (token.value == TOKunittest)
            id = Lexer::idPool(Token::toChars(TOKunittest));
        else if (token.value == TOKassert)
            id = Lexer::idPool(Token::toChars(TOKassert));
#endif
        else
            error("identifier or integer expected, not %s", token.toChars());
        nextToken();
        check(TOKrparen);

    }
    else
       error("(condition) expected following version");
    c = new VersionCondition(mod, level, id);
    return c;

}
