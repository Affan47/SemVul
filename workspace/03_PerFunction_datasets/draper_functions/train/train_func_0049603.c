AST_get_bstr(tst_t *settings, tst_t *fr, bstring name, ValueType type)
{
    Value *val = AST_get(settings, fr, name, type);

    check(val != NULL, "The server is missing the '%s' variable.",
            bdata(name), Value_type_name(type));

    return val->as.string->data;

error:
    return NULL;
}
