gdef_read_channel_meta(GDEFControlBlock *block)
{
    GwyContainer *meta;
    gchar *s;
    guint i;

    meta = gwy_container_new();
    for (i = 0; i < block->n_variables; i++) {
        GDEFVariable *var = block->variables + i;

        if (var->type == VAR_INTEGER || var->type == VAR_WORD
            || var->type == VAR_DWORD) {
            s = g_strdup_printf("%ld", (glong)gdef_get_int_var(var));
            gwy_container_set_string_by_name(meta, var->name, s);
        }
        else if (var->type == VAR_DOUBLE || var->type == VAR_FLOAT) {
            s = g_strdup_printf("%g", gdef_get_real_var(var));
            gwy_container_set_string_by_name(meta, var->name, s);
        }
    }

    s = gdef_read_channel_comment(block);
    if (s)
        gwy_container_set_string_by_name(meta, "Comment", s);
    else
        g_free(s);

    if (gwy_container_get_n_items(meta))
        return meta;

    g_object_unref(meta);
    return NULL;
}
