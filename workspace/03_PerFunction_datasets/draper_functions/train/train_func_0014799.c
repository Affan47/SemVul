variable_mangle_result(string_ty *s)
{
    static string_ty *t1;
    static string_ty *t2;
    string_ty       *tmp;

    trace(("variable_mangle_result(\"%s\")\n{\n", s->str_text));
    if (!s->str_length)
    {
        str_free(s);
        s = str_from_c("\"\"");
    }
    if (!t1)
    {
        t1 = str_from_c("/*");
        t2 = str_from_c("/\\*");
    }
    tmp = str_substitute(t1, t2, s);
    str_free(s);
    string_list_append(&result, tmp);
    str_free(tmp);
    trace(("}\n"));
}
