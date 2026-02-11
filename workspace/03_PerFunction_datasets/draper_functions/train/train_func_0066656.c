parseTemplateArgumentList2()
{

    Objects *tiargs = new Objects();
    TOK endtok = TOKrparen;
    nextToken();


    while (token.value != endtok)
    {

            if (isDeclaration(&token, 0, TOKreserved, NULL))
            {
                Type *ta = parseType();
                tiargs->push(ta);
            }
            else
            {
                Expression *ea = parseAssignExp();
                tiargs->push(ea);
            }
            if (token.value != TOKcomma)
                break;
            nextToken();
    }
    check(endtok, "template argument list");
    return tiargs;
}
