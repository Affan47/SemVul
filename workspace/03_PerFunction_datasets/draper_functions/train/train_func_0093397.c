parseAggregate()
{
    AggregateDeclaration *a = NULL;
    int anon = 0;
    Identifier *id;
    TemplateParameters *tpl = NULL;
    Expression *constraint = NULL;
    Loc loc = token.loc;
    TOK tok = token.value;


    nextToken();
    if (token.value != TOKidentifier)
    {   id = NULL;
    }
    else
    {   id = token.ident;
        nextToken();

        if (token.value == TOKlparen)
        {


            tpl = parseTemplateParameterList();
            constraint = parseConstraint();
        }
    }

    switch (tok)
    {
        case TOKclass:
        case TOKinterface:
        {
            if (!id)
                error("anonymous classes not allowed");


            BaseClasses *baseclasses = NULL;
            if (token.value == TOKcolon)
            {
                nextToken();
                baseclasses = parseBaseClasses();

                if (tpl)
                {
                    Expression *tempCons = parseConstraint();
                    if (tempCons)
                    {
                        if (constraint)
                            error("members expected");
                        else
                            constraint = tempCons;
                    }
                }

                if (token.value != TOKlcurly)
                    error("members expected");
            }

            if (tok == TOKclass)
            {
                bool inObject = md && !md->packages && md->id == Id::object;
                a = new ClassDeclaration(loc, id, baseclasses, inObject);
            }
            else
                a = new InterfaceDeclaration(loc, id, baseclasses);
            break;
        }

        case TOKstruct:
            if (id)
                a = new StructDeclaration(loc, id);
            else
                anon = 1;
            break;

        case TOKunion:
            if (id)
                a = new UnionDeclaration(loc, id);
            else
                anon = 2;
            break;

        default:
            assert(0);
            break;
    }
    if (a && token.value == TOKsemicolon)
    {   nextToken();
    }
    else if (token.value == TOKlcurly)
    {

        nextToken();
        Dsymbols *decl = parseDeclDefs(0);
        if (token.value != TOKrcurly)
            error("} expected following member declarations in aggregate");
        nextToken();
        if (anon)
        {


            return new AnonDeclaration(loc, anon == 2, decl);
        }
        else
            a->members = decl;
    }
    else
    {
        error("{ } expected following aggregate declaration");
        a = new StructDeclaration(loc, NULL);
    }

    if (tpl)
    {

        Dsymbols *decldefs = new Dsymbols();
        decldefs->push(a);
        TemplateDeclaration *tempdecl =
                new TemplateDeclaration(loc, id, tpl, constraint, decldefs, 0);
        return tempdecl;
    }

    return a;
}
