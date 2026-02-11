get_named_var (parser_env_ptr pe)
{
    var_store_ptr retp = NULL, bv;

    for (retp = pe->predefined_vars, bv = NULL; retp; retp = retp->next_var)
        if (strcmp (retp->variable_name, pe->name) == 0)
            break;

    if (!retp && pe->named_vars)
        for (retp = pe->named_vars; retp; bv = retp, retp = retp->next_var)
            if (strcmp (retp->variable_name, pe->name) == 0)
                break;

    if (!retp)
    {
        retp = g_new0 (var_store, 1);
        if (!pe->named_vars)
            pe->named_vars = retp;
        else
            bv->next_var = retp;
        retp->variable_name = g_strdup (pe->name);
        retp->type = VST_NUMERIC;
        retp->value =
            pe->trans_numeric ("0", pe->radix_point, pe->group_char, NULL);
    }

    return retp;
}
