quote_shell()
    const
{
    string_ty *tmp = str_quote_shell(ref);
    nstring result(tmp);
    str_free(tmp);
    return result;
}
