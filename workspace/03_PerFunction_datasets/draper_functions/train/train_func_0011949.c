interpret(string_list_ty *result, const string_list_ty *args,
    const expr_position_ty *pp, const struct opcode_context_ty *ocp)
{
    size_t          j;
    string_ty       *s;
    int             nbytes;
    char            buffer[2000];

    trace(("readlink(result = %p, args = %p)\n{\n", result, args));
    (void)ocp;
    for (j = 1; j < args->nstrings; ++j)
    {
        s = args->string[j];
        nbytes = readlink(s->str_text, buffer, sizeof(buffer));
        if (nbytes < 0)
        {
            sub_context_ty  *scp;

            scp = sub_context_new();
            sub_errno_set(scp);
            sub_var_set_string(scp, "File_Name", s);
            error_with_position
                (pp, scp, i18n("readlink \"$filename\": $errno"));
            sub_context_delete(scp);
            return -1;
        }
        s = str_n_from_c(buffer, nbytes);
        string_list_append(result, s);
        str_free(s);
    }
    trace(("return 0;\n"));
    trace(("}\n"));
    return 0;
}
