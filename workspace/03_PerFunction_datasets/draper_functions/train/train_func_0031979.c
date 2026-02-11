getProperty(Loc loc, Identifier *ident, int flag)
{   Expression *e;

#if LOGDOTEXP
    printf("Type::getProperty(type = '%s', ident = '%s')\n", toChars(), ident->toChars());
#endif
    if (ident == Id::__sizeof)
    {
        d_uns64 sz = size(loc);
        if (sz == SIZE_INVALID)
            return new ErrorExp();
        e = new IntegerExp(loc, sz, Type::tsize_t);
    }
    else if (ident == Id::__xalignof)
    {
        e = new IntegerExp(loc, alignsize(), Type::tsize_t);
    }
    else if (ident == Id::typeinfo)
    {
        error(loc, ".typeinfo deprecated, use typeid(type)");
        e = getTypeInfo(NULL);
    }
    else if (ident == Id::init)
    {
        Type *tb = toBasetype();
        e = defaultInitLiteral(loc);
        if (tb->ty == Tstruct && tb->needsNested())
        {
            StructLiteralExp *se = (StructLiteralExp *)e;
            se->sinit = se->sd->toInitializer();
        }
    }
    else if (ident == Id::mangleof)
    {
        if (!deco)
        {
            error(loc, "forward reference of type %s.mangleof", toChars());
            e = new ErrorExp();
        }
        else
        {
            e = new StringExp(loc, (char *)deco, strlen(deco), 'c');
            Scope sc;
            e = e->semantic(&sc);
        }
    }
    else if (ident == Id::stringof)
    {   char *s = toChars();
        e = new StringExp(loc, s, strlen(s), 'c');
        Scope sc;
        e = e->semantic(&sc);
    }
    else if (flag && this != Type::terror)
    {
        return NULL;
    }
    else
    {
        Dsymbol *s = NULL;
        if (ty == Tstruct || ty == Tclass || ty == Tenum || ty == Ttypedef)
            s = toDsymbol(NULL);
        if (s)
            s = s->search_correct(ident);
        if (this != Type::terror)
        {
            if (s)
                error(loc, "no property '%s' for type '%s', did you mean '%s'?", ident->toChars(), toChars(), s->toChars());
            else
                error(loc, "no property '%s' for type '%s'", ident->toChars(), toChars());
        }
        e = new ErrorExp();
    }
    return e;
}
