parseVariable (tokenInfo *const token)
{
    tokenInfo *const name = newToken ();


    readToken (name);
    readToken (token);
    if ( (isType (name, TOKEN_IDENTIFIER) || isType (name, TOKEN_STRING))
            && !isType (token, TOKEN_SEMICOLON) )
    {
        makeSqlTag (name, SQLTAG_VARIABLE);
    }
    if (! isType (token, TOKEN_SEMICOLON) )
        findToken (token, TOKEN_SEMICOLON);

    deleteToken (name);
}
