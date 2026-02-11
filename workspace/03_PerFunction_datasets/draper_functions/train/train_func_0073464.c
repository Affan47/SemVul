textbox_new (gint width, const gchar * text, const gchar * font,
 gboolean scroll)
{
    GtkWidget * textbox = gtk_drawing_area_new ();
    gtk_widget_set_size_request (textbox, width, 0);
    gtk_widget_add_events (textbox, GDK_BUTTON_PRESS_MASK |
     GDK_BUTTON_RELEASE_MASK);

    DRAW_CONNECT (textbox, textbox_draw);
    g_signal_connect (textbox, "destroy", (GCallback) textbox_destroy, NULL);

    TextboxData * data = g_malloc0 (sizeof (TextboxData));
    data->width = width;
    data->text = g_strdup (text);
    data->may_scroll = scroll;
    g_object_set_data ((GObject *) textbox, "textboxdata", data);

    if (font)
        data->font = pango_font_description_from_string (font);

    textboxes = g_list_prepend (textboxes, textbox);

    textbox_render (textbox, data);
    return textbox;
}
