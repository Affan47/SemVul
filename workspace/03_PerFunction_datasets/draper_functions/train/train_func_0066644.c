parseModule()
{
    Dsymbols *decldefs;


    if (token.value == TOKmodule)
    {
        Loc loc = token.loc;
        utf8_t *comment = token.blockComment;
        bool safe = FALSE;

        nextToken();
#if 0 && DMDV2
        if (token.value == TOKlparen)
        {
            nextToken();
            if (token.value != TOKidentifier)
            {   error("module (system) identifier expected");
                goto Lerr;
            }
            Identifier *id = token.ident;

            if (id == Id::system)
                safe = TRUE;
            else
                error("(safe) expected, not %s", id->toChars());
            nextToken();
            check(TOKrparen);
        }
#endif

        if (token.value != TOKidentifier)
        {   error("Identifier expected following module");
            goto Lerr;
        }
        else
        {
            Identifiers *a = NULL;
            Identifier *id;

            id = token.ident;
            while (nextToken() == TOKdot)
            {
                if (!a)
                    a = new Identifiers();
                a->push(id);
                nextToken();
                if (token.value != TOKidentifier)
                {   error("Identifier expected following package");
                    goto Lerr;
                }
                id = token.ident;
            }

            md = new ModuleDeclaration(loc, a, id, safe);

            if (token.value != TOKsemicolon)
                error("';' expected following module declaration instead of %s", token.toChars());
            nextToken();
            addComment(mod, comment);
        }
    }

    decldefs = parseDeclDefs(0);
    if (token.value != TOKeof)
    {
        error(token.loc, "unrecognized declaration");
        goto Lerr;
    }
    return decldefs;

Lerr:
    while (token.value != TOKsemicolon && token.value != TOKeof)
        nextToken();
    nextToken();
    return new Dsymbols();
}
