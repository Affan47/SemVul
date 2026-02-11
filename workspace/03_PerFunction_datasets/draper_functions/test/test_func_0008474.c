string_pref_add_entry(GtkWidget *section, guint pos, HybridPrefEntry *entry)
{
    GtkWidget *text;
    GtkWidget *label;
    gchar *value;

    label = gtk_label_new(entry->name);
    gtk_misc_set_alignment(GTK_MISC(label), 0, 0.5);
    if (entry->tooltip)
        gtk_widget_set_tooltip_markup(label, entry->tooltip);
    text = gtk_entry_new();

    value = hybrid_pref_get_string(entry->win->pref, entry->key);
    if (value) {
        gtk_entry_set_text(GTK_ENTRY(text), value);
        g_free(value);
    }

    entry->data = text;

    gtk_table_attach_defaults(GTK_TABLE(section), label, 0, 1, pos, pos + 1);
    gtk_table_attach_defaults(GTK_TABLE(section), text, 1, 2, pos, pos + 1);
    return 1;
}
