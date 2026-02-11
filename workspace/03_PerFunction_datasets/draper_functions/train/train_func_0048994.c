gwy_string_list_clone_real(GObject *source, GObject *copy)
{
    GwyStringList *strlist, *clone;
    GPtrArray *strings, *copystrings;
    guint i;

    g_return_if_fail(GWY_IS_STRING_LIST(source));
    g_return_if_fail(GWY_IS_STRING_LIST(copy));

    strlist = GWY_STRING_LIST(source);
    clone = GWY_STRING_LIST(copy);

    strings = (GPtrArray*)strlist->strings;
    copystrings = (GPtrArray*)clone->strings;
    for (i = 0; i < copystrings->len; i++)
        g_free(g_ptr_array_index(copystrings, i));
    g_ptr_array_set_size(copystrings, strings->len);
    for (i = 0; i < strings->len; i++)
        g_ptr_array_index(copystrings, i)
            = g_strdup(g_ptr_array_index(strings, i));

    g_signal_emit(copy, string_list_signals[VALUE_CHANGED], 0);
}
