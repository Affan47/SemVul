exit_parser (parser_env_ptr pe)
{
    var_store_ptr vars, bv;

    if (pe == NULL)
        return;

    for (vars = pe->named_vars; vars; vars = bv)
    {
        g_free (vars->variable_name);
        vars->variable_name = NULL;

        if (vars->value)
            pe->free_numeric (vars->value);
        vars->value = NULL;

        bv = vars->next_var;
        g_free (vars);
    }

    pe->named_vars = NULL;

    g_free (pe->stack);
    pe->stack = NULL;

    g_free (pe->tokens);
    pe->tokens = NULL;
    pe->token_tail = NULL;

    if (pe->numeric_value)
        pe->free_numeric (pe->numeric_value);
    pe->numeric_value = NULL;

    g_free (pe);
}
