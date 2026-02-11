put_cstr(const char *s)
{
    if (!s || !*s)
        return;
    wstring_ty *s2 = wstr_from_c(s);
    put_wstr(s2);
    wstr_free(s2);
}
