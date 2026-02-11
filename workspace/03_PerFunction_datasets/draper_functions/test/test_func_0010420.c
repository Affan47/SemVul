initialize(void)
{
    int             ok;
    size_t          j;
    string_ty       *s;

    if (stp)
        return 0;
    stp = symtab_alloc(5);
    leaf_file = find_variable("graph_leaf_file");
    leaf_pattern = find_variable("graph_leaf_pattern");
    interior_file = find_variable("graph_interior_file");
    interior_pattern = find_variable("graph_interior_pattern");
    exterior_file = find_variable("graph_exterior_file");
    exterior_pattern = find_variable("graph_exterior_pattern");

    if (leaf_file)
    {
        for (j = 0; j < leaf_file->nstrings; ++j)
        {
            s = leaf_file->string[j];
            ok = matches_list(s, interior_pattern);
            if (ok < 0)
                return -1;
            if (!ok)
                symtab_assign(stp, s, &leaf_explicit);
        }
    }

    if (interior_file)
    {
        for (j = 0; j < interior_file->nstrings; ++j)
        {
            s = interior_file->string[j];
            symtab_assign(stp, s, &interior_explicit);
        }
    }

    if (exterior_file)
    {
        for (j = 0; j < exterior_file->nstrings; ++j)
        {
            s = exterior_file->string[j];
            symtab_assign(stp, s, &exterior_explicit);
        }
    }

    return 0;
}
