hybrid_tooltip_data_add_pair(HybridTooltipData *data, const gchar *name,
                             const gchar *value)
{
    PangoLayout *layout;
    gchar *markup;
    gchar *escaped_name;
    gchar *escaped_value = NULL;

    g_return_if_fail(data != NULL);
    g_return_if_fail(name != NULL);

    escaped_name  = g_markup_escape_text(name, -1);

    if (value) {
        escaped_value = g_markup_escape_text(value, -1);
    } else {
        escaped_value = g_strdup("");
    }

    markup = g_strdup_printf("<b>%s:</b> %s", escaped_name, escaped_value);

    g_free(escaped_name);
    g_free(escaped_value);

    layout = create_pango_layout(markup, NULL, NULL);

    g_free(markup);

    data->layouts = g_slist_append(data->layouts, layout);
}
