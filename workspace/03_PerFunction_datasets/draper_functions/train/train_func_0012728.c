obt_prop_get_text(Window win, Atom prop, ObtPropTextType type,
                           gchar **ret_string)
{
    XTextProperty tprop;
    gchar *str;
    gboolean ret = FALSE;

    if (get_text_property(win, prop, &tprop, type)) {
        str = (gchar*)convert_text_property(&tprop, type, 1);

        if (str) {
            *ret_string = str;
            ret = TRUE;
        }
    }
    XFree(tprop.value);
    return ret;
}
