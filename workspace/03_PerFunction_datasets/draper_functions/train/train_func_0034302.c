cache_search(string_ty *filename)
{
    cache_ty        *cp;

    assert(symtab);
    cp = symtab_query(symtab, filename);
    if (!cp)
    {
        cp = mem_alloc(sizeof(cache_ty));
        memset(&cp->st, 0, sizeof(cp->st));
        string_list_constructor(&cp->ingredients);
        symtab_assign(symtab, filename, cp);
    }
    return cp;
}
