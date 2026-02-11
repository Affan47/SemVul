inferApplyArgTypesX(Expression *ethis, FuncDeclaration *fstart, Parameters *arguments)
{
  struct ParamOpOver
  {
    Parameters *arguments;
    int mod;
    MATCH match;
    FuncDeclaration *fd_best;
    FuncDeclaration *fd_ambig;

    static int fp(void *param, Dsymbol *s)
    {
        FuncDeclaration *f = s->isFuncDeclaration();
        if (!f)
            return 0;
        ParamOpOver *p = (ParamOpOver *)param;
        TypeFunction *tf = (TypeFunction *)f->type;
        MATCH m = MATCHexact;

        if (f->isThis())
        {
            if (!MODimplicitConv(p->mod, tf->mod))
                m = MATCHnomatch;
            else if (p->mod != tf->mod)
                m = MATCHconst;
        }
        if (!inferApplyArgTypesY(tf, p->arguments, 1))
            m = MATCHnomatch;

        if (m > p->match)
        {
            p->fd_best = f;
            p->fd_ambig = NULL;
            p->match = m;
        }
        else if (m == p->match)
            p->fd_ambig = f;
        return 0;
    }
  };
    ParamOpOver p;
    p.arguments = arguments;
    p.mod = ethis->type->mod;
    p.match = MATCHnomatch;
    p.fd_best = NULL;
    p.fd_ambig = NULL;
    overloadApply(fstart, &p, &ParamOpOver::fp);
    if (p.fd_best)
    {
        inferApplyArgTypesY((TypeFunction *)p.fd_best->type, arguments);
        if (p.fd_ambig)
        {   ::error(ethis->loc, "%s.%s matches more than one declaration:\n\t%s(%d):%s\nand:\n\t%s(%d):%s",
                    ethis->toChars(), fstart->ident->toChars(),
                    p.fd_best ->loc.filename, p.fd_best ->loc.linnum, p.fd_best ->type->toChars(),
                    p.fd_ambig->loc.filename, p.fd_ambig->loc.linnum, p.fd_ambig->type->toChars());
            p.fd_best = NULL;
        }
    }
    return p.fd_best;
}
