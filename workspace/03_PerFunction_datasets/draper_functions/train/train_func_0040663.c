sub_plural(sub_context_ty *scp, wstring_list_ty *arg)
{
    string_ty       *s;
    wstring_ty      *result;
    long            n;

    trace(("sub_plural()\n{\n"));
    switch (arg->nitems)
    {
    default:
        sub_context_error_set(scp, i18n("requires two or three arguments"));
        result = 0;
        break;

    case 3:
        wstring_list_append(arg, wstr_from_c(""));


    case 4:
        s = wstr_to_str(arg->item[1]);
        n = atol(s->str_text);
        str_free(s);
        if (n != 1)
            result = wstr_copy(arg->item[2]);
        else
            result = wstr_copy(arg->item[3]);
        break;
    }
    trace(("return %p;\n", result));
    trace(("}\n"));
    return result;
}
