hash_serialize_func(gpointer hkey, gpointer hvalue, gpointer hdata)
{
    GQuark key = GPOINTER_TO_UINT(hkey);
    GValue *value = (GValue*)hvalue;
    SerializeData *sdata = (SerializeData*)hdata;
    GwySerializeItem *it;
    GType type = G_VALUE_TYPE(value);
    gsize i;

    i = sdata->i;
    it = sdata->items + i;
    it->name = g_quark_to_string(key);
    switch (type) {
        case G_TYPE_BOOLEAN:
        it->ctype = 'b';
        it->value.v_boolean = !!g_value_get_boolean(value);
        break;

        case G_TYPE_UCHAR:
        it->ctype = 'c';
        it->value.v_char = g_value_get_uchar(value);
        break;

        case G_TYPE_INT:
        it->ctype = 'i';
        it->value.v_int32 = g_value_get_int(value);
        break;

        case G_TYPE_INT64:
        it->ctype = 'q';
        it->value.v_int64 = g_value_get_int64(value);
        break;

        case G_TYPE_DOUBLE:
        it->ctype = 'd';
        it->value.v_double = g_value_get_double(value);
        break;

        case G_TYPE_STRING:
        it->ctype = 's';
        it->value.v_string = (guchar*)g_value_get_string(value);
        break;

        case G_TYPE_OBJECT:
        it->ctype = 'o';
        it->value.v_object = g_value_get_object(value);
        break;

        default:
        g_warning("Cannot pack GValue holding %s", g_type_name(type));
        return;
        break;
    }

    sdata->i++;
}
