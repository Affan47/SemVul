ibus_attr_list_copy (IBusAttrList       *dest,
                     const IBusAttrList *src)
{
    gboolean retval;

    retval = IBUS_SERIALIZABLE_CLASS (ibus_attr_list_parent_class)->copy ((IBusSerializable *)dest,
                                 (IBusSerializable *)src);
    g_return_val_if_fail (retval, FALSE);

    g_return_val_if_fail (IBUS_IS_ATTR_LIST (dest), FALSE);
    g_return_val_if_fail (IBUS_IS_ATTR_LIST (src), FALSE);

    gint i;
    for (i = 0; ; i++) {
        IBusAttribute *attr = ibus_attr_list_get ((IBusAttrList *)src, i);
        if (attr == NULL) {
            break;
        }

        attr = (IBusAttribute *) ibus_serializable_copy ((IBusSerializable *) attr);
        if (attr == NULL) {
            g_warning ("can not copy attribute");
            continue;
        }

        ibus_attr_list_append (dest, attr);
    }
    return TRUE;
}
