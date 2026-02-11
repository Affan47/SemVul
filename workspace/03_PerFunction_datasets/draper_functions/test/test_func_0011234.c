set_menu_indicator(const gchar * name, gint percent)
{
    static gchar *rebuilding = NULL;

    if (name == NULL)
        set_menu_label(rebuilding_entry, "", FALSE);
    else {
        gchar *label;

        if (rebuilding == NULL)

            rebuilding = _("Rebuilding:");

        label = g_strdup_printf("%s %s (%d%%)", rebuilding, name, percent);
        set_menu_label(rebuilding_entry, label, FALSE);

        g_free(label);
    }
}
