gcut_dynamic_data_new_va_list (const gchar *first_field_name, va_list args)
{
    GCutDynamicDataPrivate *priv;
    GCutDynamicData *data;
    const gchar *name;

    data = g_object_new(GCUT_TYPE_DYNAMIC_DATA, NULL);
    priv = GCUT_DYNAMIC_DATA_GET_PRIVATE(data);
    name = first_field_name;
    while (name) {
        Field *field;

        field = field_new(data, name, va_arg(args, GType));
        switch (field->type) {
        case G_TYPE_CHAR:
            field->value.character = va_arg(args, gint);
            break;
        case G_TYPE_STRING:
            field->value.pointer = g_strdup(va_arg(args, const gchar *));
            field->free_function = g_free;
            break;
        case G_TYPE_INT:
            field->value.integer = va_arg(args, gint);
            break;
        case G_TYPE_UINT:
            field->value.unsigned_integer = va_arg(args, guint);
            break;
        case G_TYPE_INT64:
            field->value.integer64 = va_arg(args, gint64);
            break;
        case G_TYPE_UINT64:
            field->value.unsigned_integer64 = va_arg(args, guint64);
            break;
        case G_TYPE_POINTER:
            field->value.pointer = va_arg(args, gpointer);
            field->free_function = va_arg(args, GDestroyNotify);
            break;
        case G_TYPE_BOOLEAN:
            field->value.boolean = va_arg(args, gboolean);
            break;
        case G_TYPE_DOUBLE:
            field->value.double_value = va_arg(args, gdouble);
            break;
        default:
            if (field->type == GCUT_TYPE_SIZE) {
                field->value.size = va_arg(args, gsize);
            } else if (field->type == G_TYPE_GTYPE) {
                field->value.type = va_arg(args, GType);
            } else if (G_TYPE_IS_FLAGS(field->type)) {
                field->value.unsigned_integer = va_arg(args, guint);
            } else if (G_TYPE_IS_ENUM(field->type)) {
                field->value.integer = va_arg(args, gint);
            } else if (G_TYPE_IS_BOXED(field->type)) {
                field->value.pointer = va_arg(args, gpointer);
            } else if (G_TYPE_IS_OBJECT(field->type)) {
                field->value.pointer = va_arg(args, gpointer);
                field->free_function = g_object_unref;
            } else {
                g_warning("unsupported type: <%s>",
                          g_type_name(field->type));
                field_free(field);
                field = NULL;
            }
            break;
        }
        if (!field)
            break;

        g_hash_table_insert(priv->fields, g_strdup(name), field);

        name = va_arg(args, const gchar *);
    }

    return data;
}
