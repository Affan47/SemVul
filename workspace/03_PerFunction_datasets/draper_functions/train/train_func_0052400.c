flatten(Scope *sc)
{

    sc = sc->startCTFE();
    exp = exp->semantic(sc);
    exp = resolveProperties(sc, exp);
    sc = sc->endCTFE();
    exp = exp->ctfeInterpret();

    Statements *a = new Statements();
    if (exp->op != TOKerror)
    {
        StringExp *se = exp->toString();
        if (!se)
           error("argument to mixin must be a string, not (%s)", exp->toChars());
        else
        {
            se = se->toUTF8(sc);
            Parser p(sc->module, (utf8_t *)se->string, se->len, 0);
            p.scanloc = loc;
            p.nextToken();

            while (p.token.value != TOKeof)
            {
                unsigned errors = global.errors;
                Statement *s = p.parseStatement(PSsemi | PScurlyscope);
                if (!s || global.errors != errors)
                    goto Lerror;
                a->push(s);
            }
            return a;
        }
    }
Lerror:
    a->push(new ErrorStatement());
    return a;
}
