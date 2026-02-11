prepost_interpret(string_list_ty *result, const string_list_ty *args,
    const expr_position_ty *pp, const struct opcode_context_ty *ocp)
{
    size_t          j;

    trace(("prepost\n"));
    (void)ocp;
    assert(result);
    assert(args);
    assert(args->nstrings);
    if (args->nstrings < 3)
    {
        sub_context_ty  *scp;

        scp = sub_context_new();
        sub_var_set_string(scp, "Name", args->string[0]);
        error_with_position
        (
            pp,
            scp,
            i18n("$name: requires two or more arguments")
        );
        sub_context_delete(scp);
        return -1;
    }
    for (j = 3; j < args->nstrings; j++)
    {
        string_ty       *s;

        s = str_cat_three(args->string[1], args->string[j], args->string[2]);
        string_list_append(result, s);
        str_free(s);
    }
    return 0;
}
