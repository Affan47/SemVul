stripDefaultArgs(Type *t)
{
  struct N
  {
    static Parameters *stripParams(Parameters *arguments)
    {
        Parameters *args = arguments;
        if (args && args->dim > 0)
        {
            for (size_t i = 0; i < args->dim; i++)
            {
                Parameter *a = (*args)[i];
                Type *ta = stripDefaultArgs(a->type);
                if (ta != a->type || a->defaultArg || a->ident)
                {
                    if (args == arguments)
                    {
                        args = new Parameters();
                        args->setDim(arguments->dim);
                        for (size_t j = 0; j < args->dim; j++)
                            (*args)[j] = (*arguments)[j];
                    }
                    (*args)[i] = new Parameter(a->storageClass, ta, NULL, NULL);
                }
            }
        }
        return args;
    }
  };

    if (t == NULL)
        return t;

    if (t->ty == Tfunction)
    {
        TypeFunction *tf = (TypeFunction *)t;
        Type *tret = stripDefaultArgs(tf->next);
        Parameters *args = N::stripParams(tf->parameters);
        if (tret == tf->next && args == tf->parameters)
            goto Lnot;
        tf = (TypeFunction *)tf->copy();
        tf->parameters = args;
        tf->next = tret;

        t = tf;
    }
    else if (t->ty == Ttuple)
    {
        TypeTuple *tt = (TypeTuple *)t;
        Parameters *args = N::stripParams(tt->arguments);
        if (args == tt->arguments)
            goto Lnot;
        t = new TypeTuple(args);
    }
    else if (t->ty == Tenum)
    {

        goto Lnot;
    }
    else
    {
        Type *tn = t->nextOf();
        Type *n = stripDefaultArgs(tn);
        if (n == tn)
            goto Lnot;
        t = t->copy();
        ((TypeNext *)t)->next = n;
    }

Lnot:
    return t;
}
