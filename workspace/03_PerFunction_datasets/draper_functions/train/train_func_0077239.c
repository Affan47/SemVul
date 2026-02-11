interpret(string_list_ty *result, const string_list_ty *args,
    const expr_position_ty *pp, const struct opcode_context_ty *ocp)
{
    table_ty        *tp;
    string_ty       *s;
    size_t          j;

    trace(("options\n"));
    (void)ocp;
    if (args->nstrings != 1)
    {
        sub_context_ty  *scp;

        scp = sub_context_new();
        sub_var_set_string(scp, "Name", args->string[0]);
        error_with_position(pp, scp, i18n("$name: requires no arguments"));
        sub_context_delete(scp);
        return -1;
    }


    for (tp = table; tp < ENDOF(table); ++tp)
    {
        s = str_from_c(option_test(tp->option) ? tp->set : tp->unset);
        string_list_append(result, s);
        str_free(s);
    }


    for (j = 0; j < option.o_search_path.nstrings; ++j)
    {
        s = str_format("-I%s", option.o_search_path.string[j]->str_text);
        string_list_append(result, s);
        str_free(s);
    }


    s = str_from_c("-nolog");
    string_list_append(result, s);
    str_free(s);
    return 0;
}
