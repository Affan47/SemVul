parse_value_free(ObtDDParseValue *v)
{
    switch (v->type) {
    case OBT_DDPARSE_EXEC:
    case OBT_DDPARSE_STRING:
    case OBT_DDPARSE_LOCALESTRING:
        g_free(v->value.string); break;
    case OBT_DDPARSE_STRINGS:
    case OBT_DDPARSE_LOCALESTRINGS:
        g_strfreev(v->value.strings.a);
        v->value.strings.n = 0;
        break;
    case OBT_DDPARSE_BOOLEAN:
    case OBT_DDPARSE_NUMERIC:
    case OBT_DDPARSE_ENUM_TYPE:
    case OBT_DDPARSE_ENVIRONMENTS:
        break;
    default:
        g_assert_not_reached();
    }
    g_slice_free(ObtDDParseValue, v);
}
