delete_var (char *var_name, parser_env_ptr pe)
{
    unsigned ret = FALSE;
    var_store_ptr nv, tv;

    if (pe == NULL)
        return FALSE;

    for (nv = pe->named_vars, tv = NULL; nv; tv = nv, nv = nv->next_var)
    {
        if (strcmp (nv->variable_name, var_name) == 0)
        {
            if (tv)
                tv->next_var = nv->next_var;
            else
                pe->named_vars = nv->next_var;

            g_free (nv->variable_name);
            nv->variable_name = NULL;

            pe->free_numeric (nv->value);
            nv->value = NULL;

            g_free (nv);

            ret = TRUE;
            break;
        }
    }

    return ret;
}
