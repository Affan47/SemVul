graph_file_pair_foreign_derived(graph_file_pair_ty *gfpp,
    const string_list_ty *slp)
{
    size_t          j;
    string_ty       *fn;

    if (!gfpp->foreign_derived)
        gfpp->foreign_derived = symtab_alloc(slp->nstrings);
    for (j = 0; j < slp->nstrings; ++j)
    {
        fn = slp->string[j];
        symtab_assign(gfpp->foreign_derived, fn, fn);
    }
}
