checkDefCtor(Loc loc, Type *t)
{
    t = t->baseElemOf();
    if (t->ty == Tstruct)
    {
        StructDeclaration *sd = ((TypeStruct *)t)->sym;
        if (sd->noDefaultCtor)
        {
            sd->error(loc, "default construction is disabled");
            return true;
        }
    }
    return false;
}
