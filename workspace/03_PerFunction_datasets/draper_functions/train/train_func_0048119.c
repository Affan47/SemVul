semantic(Scope *sc)
{


    if (scope)
    {   sc = scope;
        scope = NULL;
    }

    if (!type)
        type = new TypeFunction(NULL, Type::tvoid, FALSE, LINKd);


    if (inTemplateInstance() && semanticRun < PASSsemantic)
    {


        Identifier *id = Lexer::idPool("__gate");
        VarDeclaration *v = new VarDeclaration(Loc(), Type::tint32, id, NULL);
        v->storage_class = isSharedStaticCtorDeclaration() ? STCstatic : STCtls;
        Statements *sa = new Statements();
        Statement *s = new ExpStatement(Loc(), v);
        sa->push(s);
        Expression *e = new IdentifierExp(Loc(), id);
        e = new AddAssignExp(Loc(), e, new IntegerExp(1));
        e = new EqualExp(TOKnotequal, Loc(), e, new IntegerExp(1));
        s = new IfStatement(Loc(), NULL, e, new ReturnStatement(Loc(), NULL), NULL);
        sa->push(s);
        if (fbody)
            sa->push(fbody);
        fbody = new CompoundStatement(Loc(), sa);
    }

    FuncDeclaration::semantic(sc);


    Module *m = getModule();
    if (!m)
        m = sc->module;
    if (m)
    {   m->needmoduleinfo = 1;

    }
}
