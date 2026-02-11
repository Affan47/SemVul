set_text_tag_from_style(GtkTextTag *tag, GtkStyle *style, GtkStyle *base_style)
{
    g_object_set(tag, "foreground-set", FALSE, NULL);
    g_object_set(tag, "background-set", FALSE, NULL);
    g_object_set(tag, "font-desc", NULL, NULL);

    if (memcmp(
        &style->fg[GTK_STATE_NORMAL],
        &base_style->fg[GTK_STATE_NORMAL],
        sizeof(GdkColor)))

        g_object_set(tag, "foreground-gdk", &style->fg[GTK_STATE_NORMAL], NULL);

    if (memcmp(
        &style->bg[GTK_STATE_NORMAL],
        &base_style->bg[GTK_STATE_NORMAL],
        sizeof(GdkColor)))

        g_object_set(tag, "background-gdk", &style->bg[GTK_STATE_NORMAL], NULL);

    if (style->font_desc != base_style->font_desc)
        g_object_set(tag, "font-desc", style->font_desc, NULL);
}
