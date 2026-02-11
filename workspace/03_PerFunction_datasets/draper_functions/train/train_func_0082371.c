interpret(string_list_ty *result, const string_list_ty *args,
    const expr_position_ty *pp, const struct opcode_context_ty *ocp)
{
    size_t          j;

    trace(("opsys\n"));
    (void)ocp;
    if (!stp)
    {
        find_out_about_system();
        assert(stp);
    }
    if (args->nstrings < 2)
    {
        static string_ty *name;
        string_ty       *value;

        if (!name)
            name = str_from_c("name");
        value = symtab_query(stp, name);
        assert(value);
        string_list_append(result, value);
    }
    for (j = 1; j < args->nstrings; j++)
    {
        string_ty       *name;
        string_ty       *value;

        name = args->string[j];
        value = symtab_query(stp, name);
        if (!value)
        {
            sub_context_ty  *scp;

            scp = sub_context_new();
            sub_var_set_string(scp, "Name", args->string[0]);
            sub_var_set_string(scp, "ATTRibute", name);
            error_with_position
            (
                pp,
                scp,
                i18n("$name: unknown \"$attribute\" attribute")
            );
            sub_context_delete(scp);
            return -1;
        }
        string_list_append(result, value);
    }
    return 0;
}
