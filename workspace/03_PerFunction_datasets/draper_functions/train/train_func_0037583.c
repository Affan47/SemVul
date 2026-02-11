semantic(Loc loc, Scope *sc)
{

    int errors = global.errors;
    sym->semantic(sc);
    if (errors != global.errors || sym->errors || sym->basetype->ty == Terror)
        return terror;
    return merge();
}
