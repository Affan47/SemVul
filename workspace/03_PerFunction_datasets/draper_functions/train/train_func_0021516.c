AST_str(tst_t *settings, tst_t *fr, const char *name, TokenType type)
{
    bstring key = bfromcstr(name);
    bstring val = AST_get_bstr(settings, fr, key, type);
    bdestroy(key);
    return bdata(val);
}
