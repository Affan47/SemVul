filename(input_ty *this)
{
    static string_ty *s;

    (void)this;
    if (!s)
        s = str_from_c("/dev/null");
    return s;
}
