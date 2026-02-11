gwy_string_list_finalize(GObject *object)
{
    GwyStringList *strlist = (GwyStringList*)object;
    GPtrArray *strings;

    strings = (GPtrArray*)strlist->strings;
    if (strings) {
        g_ptr_array_free(strings, TRUE);
        strlist->strings = NULL;
    }

    G_OBJECT_CLASS(gwy_string_list_parent_class)->finalize(object);
}
