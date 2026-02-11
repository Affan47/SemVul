leaf_query(string_ty *filename, int probe)
{
    leaf_ness_ty    *d;
    time_t          t;
    int             ok;
    opcode_context_ty *ocp;


    if (!stp)
    {
        ok = initialize();
        if (ok < 0)
            return leaf_ness_error;
    }


    d = symtab_query(stp, filename);
    if (d)
        return *d;


    ok = matches_list(filename, exterior_pattern);
    if (ok < 0)
        return leaf_ness_error;
    if (ok)
    {
        symtab_assign(stp, filename, &exterior_explicit);
        return leaf_ness_exterior_explicit;
    }
    ok = matches_list(filename, interior_pattern);
    if (ok < 0)
        return leaf_ness_error;
    if (ok)
    {
        symtab_assign(stp, filename, &interior_explicit);
        return leaf_ness_interior_explicit;
    }


    if (leaf_file || leaf_pattern)
    {


        ok = matches_list(filename, leaf_pattern);
        if (ok < 0)
            return leaf_ness_error;
        if (ok)
        {
            symtab_assign(stp, filename, &leaf_explicit);
            return leaf_ness_leaf_explicit;
        }


        symtab_assign(stp, filename, &interior_explicit);
        return leaf_ness_interior_explicit;
    }


    if (!probe)
        return leaf_ness_indeterminate;


    ocp = opcode_context_new(0, 0);
    t = cook_mtime_oldest(ocp, filename, (long *)0, 32767L);
    opcode_context_delete(ocp);
    if (t < 0)
        return leaf_ness_error;
    if (t != 0)
    {
        symtab_assign(stp, filename, &leaf_exists);
        return leaf_ness_leaf_exists;
    }
    symtab_assign(stp, filename, &interior_exists);
    return leaf_ness_interior_exists;
}
