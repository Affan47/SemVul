parseContracts(FuncDeclaration *f)
{
    LINK linksave = linkage;


    linkage = LINKd;
L1:
    switch (token.value)
    {
        case TOKlcurly:
            if (f->frequire || f->fensure)
                error("missing body { ... } after in or out");
            f->fbody = parseStatement(PSsemi);
            f->endloc = endloc;
            break;

        case TOKbody:
            nextToken();
            f->fbody = parseStatement(PScurly);
            f->endloc = endloc;
            break;

        case TOKsemicolon:
            if (f->frequire || f->fensure)
                error("missing body { ... } after in or out");
            nextToken();
            break;

#if 0

        case TOKcomma:
            nextToken();
            continue;
#endif

#if 0
        case TOKthrow:
            if (!f->fthrows)
                f->fthrows = new Types();
            nextToken();
            check(TOKlparen);
            while (1)
            {
                Type *tb = parseBasicType();
                f->fthrows->push(tb);
                if (token.value == TOKcomma)
                {   nextToken();
                    continue;
                }
                break;
            }
            check(TOKrparen);
            goto L1;
#endif

        case TOKin:
            nextToken();
            if (f->frequire)
                error("redundant 'in' statement");
            f->frequire = parseStatement(PScurly | PSscope);
            goto L1;

        case TOKout:

            nextToken();
            if (token.value != TOKlcurly)
            {
                check(TOKlparen);
                if (token.value != TOKidentifier)
                    error("(identifier) following 'out' expected, not %s", token.toChars());
                f->outId = token.ident;
                nextToken();
                check(TOKrparen);
            }
            if (f->fensure)
                error("redundant 'out' statement");
            f->fensure = parseStatement(PScurly | PSscope);
            goto L1;

        default:
            if (!f->frequire && !f->fensure)
                error("semicolon expected following function declaration");
            break;
    }
    linkage = linksave;
}
